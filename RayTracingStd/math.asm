;******************************************************************************
;
; Copyright (c) 1999 Advanced Micro Devices, Inc.
;
; LIMITATION OF LIABILITY:  THE MATERIALS ARE PROVIDED *AS IS* WITHOUT ANY
; EXPRESS OR IMPLIED WARRANTY OF ANY KIND INCLUDING WARRANTIES OF MERCHANTABILITY,
; NONINFRINGEMENT OF THIRD-PARTY INTELLECTUAL PROPERTY, OR FITNESS FOR ANY
; PARTICULAR PURPOSE.  IN NO EVENT SHALL AMD OR ITS SUPPLIERS BE LIABLE FOR ANY
; DAMAGES WHATSOEVER (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF PROFITS,
; BUSINESS INTERRUPTION, LOSS OF INFORMATION) ARISING OUT OF THE USE OF OR
; INABILITY TO USE THE MATERIALS, EVEN IF AMD HAS BEEN ADVISED OF THE POSSIBILITY
; OF SUCH DAMAGES.  BECAUSE SOME JURISDICTIONS PROHIBIT THE EXCLUSION OR LIMITATION
; OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES, THE ABOVE LIMITATION MAY
; NOT APPLY TO YOU.
;
; AMD does not assume any responsibility for any errors which may appear in the
; Materials nor any responsibility to support or update the Materials.  AMD retains
; the right to make changes to its test specifications at any time, without notice.
;
; NO SUPPORT OBLIGATION: AMD is not obligated to furnish, support, or make any
; further information, software, technical information, know-how, or show-how
; available to you.
;
; So that all may benefit from your experience, please report  any  problems
; or  suggestions about this software to 3dsdk.support@amd.com
;
; AMD Developer Technologies, M/S 585
; Advanced Micro Devices, Inc.
; 5900 E. Ben White Blvd.
; Austin, TX 78741
; 3dsdk.support@amd.com
;
;******************************************************************************
;
; MATH.ASM
;
; AMD3D 3D library code: Math primitives
;
;******************************************************************************

        TITLE   math.asm
        .586
        .K3D
        ASSUME cs:FLAT,ds:FLAT,es:FLAT,fs:FLAT,gs:FLAT


;******************************************************************************
; EQU   - equates and compile time constants
;******************************************************************************
ML2H    =   0bf318000h
MASKSMH =   0807fffffh          ;; mask for sign and significand
MASKSH  =   080000000h          ;; mask for sign bit


;******************************************************************************
; DATA - segment and definitions
;******************************************************************************
_DATA       SEGMENT PUBLIC PAGE USE32 'DATA'

;******************************************************************************
; Vector (3DNow!) data 
;******************************************************************************
PMOne       dq      0BF8000003F800000h      ; real4 1.0, -1.0
HalfVal     dq      03F0000003F000000h      ; real4 0.5, 0.5
HalfMin     dq      0BF0000003F000000h      ; real4 0.5, -0.5f
ones        dq      03F8000003F800000h      ; real4 1.0, 1.0
twos        dq      04000000040000000h      ; real4 2.0, 2.0
pinfs       dq      07f8000007f800000h      ; dword PINH, PINH
smh_masks   dq      0807fffff807fffffh      ; dword MASKSMH, MASKSMH
sign_mask   dq      07fffffff7fffffffh      ;
sh_masks    dq      08000000080000000h      ; dword MASKSH, MASKSH
two_126s    dq      00000007E0000007Eh      ; dword 126, 126
negh_mask   dq      08000000000000000h      ; dword 0, 080000000h (pxor same as pfmul by PMOne)

ooln2s      dq      03FB8AA3B3FB8AA3Bh      ; ln2 | ln2


; SINCOS specific values
pio4ht      dq      0b97daa22bf490000h      ; -0.000241913 | -0.785156
mo56_42     dq      0bcc30c31bc924925h      ; -0.0238095 | -0.0178571
pio4s       dq      03f490fdb3f490fdbh      ; 0.785398 | 0.785398
mo30_20     dq      0bd4ccccdbd088889h      ; -0.05 | -0.0333333
mo12_6      dq      0be2aaaabbdaaaaabh      ; -0.166667 | -0.0833333
mo2s        dq      0bf000000bf000000h      ; -0.5 | -0.5
iones       dq      00000000100000001h      ; 1 | 1


;******************************************************************************
; Scalar (single float) data
;******************************************************************************

sgn         dd      080000000h              ; mask for sign bit
mabs        dd      07FFFFFFFh              ; mask for absolute value (~sgn)
mant        dd      0007FFFFFh              ; mask for mantissa
expo        dd      07F800000h              ; mask for exponent
one         dd      03F800000h              ; 1.0f
half        dd      03F000000h              ; 0.5f
two         dd      040000000h              ; 2.0
oob         dd      000000000h              ; "out of bounds" value
nan         dd      07fffffffh              ; "Not a number" value
n0          dd      040A008EFh
n1          dd      03DAA7B3Dh
d0          dd      0412008EFh
qq0         dd      0419D92C8h
qq1         dd      041E6BD60h
qq2         dd      041355DC0h
pp0         dd      0C0D21907h
pp1         dd      0C0B59883h
pp2         dd      0BF52C7EAh
bnd         dd      03F133333h
asp0        dd      03F6A4AA5h
asp1        dd      0BF004C2Ch
asq0        dd      040AFB829h
asq1        dd      0C0AF5123h
pio2        dd      03FC90FDBh
npio2       dd      0BFC90FDBh
ooln2       dd      03FB8AA3Bh
upper       dd      042B17218h
lower       dd      0C2AEAC50h
ln2hi       dd      03F317200h
ln2lo       dd      035BFBE8Eh
rt2         dd      03FB504F3h
edec        dd      000800000h
bias        dd      00000007Fh
c2          dd      03E18EFE2h
c1          dd      03E4CAF6Fh
c0          dd      03EAAAABDh
tl2e        dd      04038AA3Bh
maxn        dd      0FF7FFFFFh
q1          dd      043BC00B5h
p1          dd      041E77545h
q0          dd      045E451C5h
p0          dd      0451E424Bh
mine        dd      0C2FC0000h
maxe        dd      043000000h
max         dd      07F7FFFFFh              ; FLT_MAX
rle10       dd      03ede5bdbh              ; 1/ln10

; SINCOS specific values
fouropi     dd      03fa2f983h              ; 1.27324f
xmax        dd      046c90fdbh              ; 25735.9

_DATA       ENDS


;******************************************************************************
; SINCOSMAC - sin/cos simultaneous computation
; Input:    mm0 - angle in radians
; Output:   mm0 - (sin|cos)
; Uses:     mm0-mm7, eax, ebx, ecx, edx, esi
; Comment:  This macro simultaneously computes sin and cos of the input
;           parameter, and returns the result packed in mm0 as (sin|cos).
;           Ultimately, this routine needs higher precision and a more
;           efficient implementation (less inter-register bank traffic).
;******************************************************************************
SINCOSMAC   MACRO
        movd        eax,mm0
        movq        mm1,mm0
        movd        mm3,[mabs]
        mov         ebx,eax
        mov         edx,eax
        pand        mm0,mm3                 ;; m0 = fabs(x)
        and         ebx,080000000h          ;; get sign bit
        shr         edx,01fh
        xor         eax,ebx                 ;; sign(ebx) = sign(eax)
        cmp         eax,[xmax]
        movd        mm2,[fouropi]
        jl          short x2
        movd        mm0,[one]
        jmp         ending
        ALIGN       32
x2:
        movq        mm1,mm0
        pfmul       mm0,mm2                 ;; mm0 = fabs(x) * 4 / PI
        movq        mm3,[pio4ht]
        pf2id       mm0,mm0
        movq        mm7,[mo56_42]
        movd        ecx,mm0
        pi2fd       mm0,mm0
        mov         esi,ecx
        movq        mm6,[mo30_20]
        punpckldq   mm0,mm0
        movq        mm5,[ones]
        pfmul       mm0,mm3
        movq        mm3,[pio4s]
        pfadd       mm1,mm0
        shr         esi,2
        punpckhdq   mm0,mm0
        xor         edx,esi
        pfadd       mm1,mm0
        test        ecx,1
        punpckldq   mm1,mm1
        jz          short x5
        pfsubr      mm1,mm3
x5:     movq        mm2,mm5
        shl         edx,01fh
        punpckldq   mm2,mm1
        pfmul       mm1,mm1
        mov         esi,ecx
        movq        mm4,[mo12_6]
        shr         esi,1
        pfmul       mm7,mm1
        xor         ecx,esi
        pfmul       mm6,mm1
        shl         esi,01fh
        pfadd       mm7,mm5
        xor         ebx,esi
        pfmul       mm4,mm1
        pfmul       mm7,mm6
        movq        mm6,[mo2s]
        pfadd       mm7,mm5
        pfmul       mm6,mm1
        pfmul       mm4,mm7
        movd        mm0,edx
        pfadd       mm4,mm5
        punpckldq   mm6,mm5
        psrlq       mm5,32
        pfmul       mm4,mm6
        punpckldq   mm0,mm0
        movd        mm1,ebx
        pfadd       mm4,mm5
        test        ecx,1
        pfmul       mm4,mm2
        jz          short x7
        punpckldq   mm5,mm4
        punpckhdq   mm4,mm5
x7:     pxor        mm4,mm1
        pxor        mm0,mm4
ending:
        ENDM


;******************************************************************************
;******************************************************************************
_TEXT   SEGMENT PUBLIC USE32 PAGE 'CODE'


;******************************************************************************
; Routine:  a_atan
; Input:    mm0.lo
; Result:   mm0.lo
; Uses:     mm0-mm7
; Comment:
;   Compute atan(x) using MMX and 3DNow! instructions.Scalar version.
;
;   If the input has an exponent of 0xFF, the result of this routine
;   is undefined. Inputs with an exponent of 0 are treated as true
;   zeroes and return a function value of 0. Result can not overflow.
;
;   atan(x) = sign(x)*atan(abs(x). If x > 1, atan(x) = pi/2-atan(1/x)
;   atan(x) for -1 <= x <= 1 is approximated by a rational minimax
;   approximation.
;
;   Testing shows that this function has an error of less than 2.27
;   single precision ulps
;
;   input      mm0.low argument x
;   output     mm0.low result atan(x)
;   destroys   mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7
;******************************************************************************
ALIGN   32
PUBLIC  _a_atan
_a_atan PROC
        movd        mm7, [sgn]  ; mask to extract sign bit
        movd        mm5, [mabs] ; mask to clear sign bit
        pand        mm7, mm0    ; sign(x)
        movd        mm6, [one]  ; 1.0
        pand        mm0, mm5    ; z=abs(x)
        pcmpgtd     mm6, mm0    ; z < 1 ? 0xffffffff : 0
        pfrcp       mm2, mm0    ; 1/z approx
        movq        mm1, mm0    ; save z
        pfrcpit1    mm0, mm2    ; 1/z step
        movd        mm3, [qq2]  ; qq2
        pfrcpit2    mm0, mm2    ; 1/z final
        movd        mm4, [pp2]  ; pp2
        pfmin       mm0, mm1    ; z = z < 1 ? z : 1/z
        movq        mm1, mm0    ; save z
        pfmul       mm0, mm0    ; z^2
        movd        mm5, [pp1]  ; pp1
        pfadd       mm3, mm0    ; z^2 + qq2
        pfmul       mm4, mm0    ; pp2 * z^2
        movd        mm2, [qq1]  ; qq1
        pfmul       mm3, mm0    ; (z^2 + qq2) * z^2
        pfadd       mm4, mm5    ; p2 * z^2 + pp1
        movd        mm5, [pp0]  ; pp0
        pfadd       mm3, mm2    ; (z^2 + qq2) * z^2 + qq1
        pfmul       mm4, mm0    ; (p2 * z^2 + pp1) * z^2
        movd        mm2, [qq0]  ; qq0
        pfmul       mm3, mm0    ; ((z^2 + qq2) * z^2 + qq1) * z^2
        pfadd       mm4, mm5    ; (p2 * z^2 + pp1) * z^2 + pp0
        pfadd       mm3, mm2    ; qx=((z^2 + qq2) * z^2 + qq1) * z^2 + qq0
        pfmul       mm0, mm4    ; ((p2 * z^2 + pp1) * z^2 + pp0) * z^2
        pfmul       mm0, mm1    ; px*z^3=((p2 * z^2 + pp1) * z^2 + pp0) * z^3
        pfrcp       mm5, mm3    ; 1/qx approx
        movd        mm4, [pio2] ; pi/2
        pfrcpit1    mm3, mm5    ; 1/qx step
        pfrcpit2    mm3, mm5    ; 1/qx final
        pfmul       mm0, mm3    ; z^3*px/qx
        pfadd       mm0, mm1    ; res=z + z^3 * px/qx 
        pfsub       mm4, mm0    ; pi/2-res
        pandn       mm6, mm4    ; z < 1 ? 0 : pi/2-res
        pfmax       mm0, mm6    ; atan(abs(x)) = z < 1 ? res : pi/2-res
        por         mm0, mm7    ; atan(x)=sign(x)*atan(abs(x))
        ret
_a_atan ENDP


;******************************************************************************
; Routine:  a_atan2
; Input:    mm0.lo = x
;           mm1.lo = y
; Result:   mm0.lo = atan2 (y, x)
; Uses:     mm0-mm7
; Comment:
;   Compute atan2(y,x) using MMX and 3DNow! instructions.Scalar version.
;
;   If the input has an exponent of 0xFF, the result of this routine
;   is undefined. Inputs with an exponent of 0 are treated as true
;   zeroes and return a function value of 0. Result can not overflow.
;
;   atan(x) = sign(x)*atan(abs(x). If x > 1, atan(x) = pi/2-atan(1/x)
;   atan(x) for -1 <= x <= 1 is approximated by a rational minimax
;   approximation.
;
;   Testing shows that this function has an error of less than 2.27
;   single precision ulps
;
;   input      mm0.low argument x
;   output     mm0.low result atan(x)
;   destroys   mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7
;******************************************************************************
ALIGN   32
PUBLIC  _a_atan2
_a_atan2 PROC

        movd        mm7, [sgn]  ; mask to extract sign bit
        movd        mm6, [sgn]  ; mask to extract sign bit
        movd        mm5, [mabs] ; mask to clear sign bit
        pand        mm7, mm0    ; xs = sign(x)
        pand        mm6, mm1    ; ys = sign(y)
        psrld       mm7, 1      ; xs >> 1
        por         mm7, mm6    ; bit<31> = ys, bit<30> = xs
        pand        mm1, mm5    ; ya = abs(y)
        pand        mm0, mm5    ; xa = abs(x)
        movq        mm6, mm1    ; ya
        movq        mm2, mm0    ; save xa
        pcmpgtd     mm6, mm0    ; df = (xa < ya) ? 0xfffffff : 0
        pfmax       mm0, mm1    ; ma = max(xa,ya)
        pslld       mm6, 31     ; df = bit<31>
        pfmin       mm1, mm2    ; mi = min(xa,ya)
        pfrcp       mm2, mm0    ; 1/ma approx
        movd        mm5, pp1    ; pp1
        pfrcpit1    mm0, mm2    ; 1/ma step
        movd        mm4, pp2    ; pp2
        pfrcpit2    mm0, mm2    ; 1/ma final
        movd        mm3, qq2    ; qq2
        pfmul       mm0, mm1    ; r = mi/ma = mi*(1/ma)
        movq        mm1, mm0    ; save r
        pfmul       mm0, mm0    ; r^2
        pfadd       mm3, mm0    ; r^2 + qq2
        pfmul       mm4, mm0    ; pp2 * r^2
        movd        mm2, qq1    ; qq1
        pfmul       mm3, mm0    ; (r^2 + qq2) * z^2
        pfadd       mm4, mm5    ; p2 * r^2 + pp1
        movd        mm5, pp0    ; pp0
        pfadd       mm3, mm2    ; (z^2 + qq2) * z^2 + qq1
        pfmul       mm4, mm0    ; (p2 * r^2 + pp1) * r^2
        movd        mm2, qq0    ; qq0
        pfmul       mm3, mm0    ; ((r^2 + qq2) * r^2 + qq1) * r^2
        pfadd       mm4, mm5    ; (p2 * r^2 + pp1) * r^2 + pp0
        pfadd       mm3, mm2    ; qx=((r^2 + qq2) * r^2 + qq1) * r^2 + qq0
        pfmul       mm0, mm4    ; ((p2 * r^2 + pp1) * r^2 + pp0) * r^2
        movq        mm4, mm7    ; ys, xs
        pfmul       mm0, mm1    ; px*r^3=((p2 * r^2 + pp1) * r^2 + pp0) * r^3
        pfrcp       mm5, mm3    ; 1/qx approx 
        pslld       mm7, 1      ; xs = bit<31>
        pfrcpit1    mm3, mm5    ; 1/qx step
        pfrcpit2    mm3, mm5    ; 1/qx final
        movq        mm5, mm7    ; xs
        pxor        mm7, mm6    ; xs^df ? 0x80000000 : 0
        pfmul       mm0, mm3    ; r^3*px/qx
        movd        mm3, npio2  ; -pi/2
        pxor        mm5, mm3    ; xs ? pi/2 : -pi/2
        psrad       mm6, 31     ; df ? 0xffffffff : 0
        pfadd       mm0, mm1    ; atan(r) = r + r^3 * px/qx
        pandn       mm6, mm5    ; xs ? (df ? 0 : pi/2) : (df ? 0 : -pi/2)
        movd        mm1, sgn    ; mask for sign bit (to isolate ys)
        pfsub       mm6, mm3    ; pr = pi/2+(xs?(df ? 0 : pi/2):(df ? 0 : -pi/2))
        por         mm0, mm7    ; ar = xs^df ? -atan(r) : atan(r)
        
        ; here  xs df  pr     ar
        ;
        ;        0 0   0      atan(r)
        ;        0 1   pi/2   -atan(r)
        ;        1 0   pi     -atan(r)
        ;        1 1   pi/2   atan(r)
        
        pand        mm1, mm4    ; ys
        pfadd       mm0, mm6    ; res = ar + pr
        por         mm0, mm1    ; atan2(y,x) = ys * res
        ret
_a_atan2 ENDP


;******************************************************************************
; Routine:  a_acos
; Input:    mm0.lo
; Result:   mm0.lo
; Uses:     mm0-mm7
; Comment:
;   Compute acos(x) using MMX and 3DNow! instructions.Scalar version.

;   If the input has an exponent of 0xFF, the result of this routine
;   is undefined. If the absolute value of the input is greater than
;   1, a special result is returned (currently this is 0). Results
;   for arguments in [-1, 1] are in [-pi/2, pi/2].
;
;   Let z=abs(x). Then acos(x) can be computed as follows:
;
;    -1 <= x <= -0.575: acos(x) = pi - 2 * asin(sqrt((1-z)/2))
;    -0.575 <= x < 0  : acos(x) = pi/2 + asin(z)
;    0 <= x < 0.575   : acos(x) = pi/2 - asin(z)
;    0.575 <= x <= 1  : acos(x) = 2 * asin(sqrt((1-z)/2))
;
;   asin(z) for 0 <= z <= 0.575 is approximated by a rational minimax
;   approximation.
;
;   Testing shows that this function has an error of less than 3.07
;   single precision ulps.
;
;******************************************************************************
ALIGN   32
PUBLIC  _a_acos
_a_acos PROC
   
        movd        mm6, [sgn]  ; mask for sign bit
        movd        mm7, [mabs] ; mask for absolute value
        movd        mm4, [half] ; 0.5
        pand        mm6, mm0    ; extract sign bit
        movd        mm5, [one]  ; 1.0
        pand        mm0, mm7    ; z = abs(x)
        movq        mm3, mm0    ; z
        pcmpgtd     mm3, mm5    ; z > 1.0 ? 0xFFFFFFFF : 0
        movq        mm5, mm0    ; save z
        pfmul       mm0, mm4    ; z*0.5
        movd        mm2, [bnd]  ; 0.575
        pfsubr      mm0, mm4    ; 0.5 - z * 0.5
        pfrsqrt     mm7, mm0    ; 1/sqrt((1-z)/2) approx low
        movq        mm1, mm7    ; complete
        pfmul       mm7, mm7    ;  reciprocal
        pcmpgtd     mm2, mm5    ; z < 0.575 ? 0xfffffff : 0
        pfrsqit1    mm7, mm0    ;   square root
        movd        mm4, [asq1] ; asq1
        pfrcpit2    mm7, mm1    ;    computation
        pfmul       mm7, mm0    ; sqrt((1-z)/2)
        movq        mm0, mm2    ; duplicate mask
        pand        mm5, mm2    ; z < 0.575 ? z : 0
        pandn       mm0, mm7    ; z < 0.575 ? 0 : sqrt((1-z)/2)
        movd        mm7, [asp1] ; asp1
        por         mm0, mm5    ; z < 0.575 ? z : sqrt((1-z)/2)
        movq        mm1, mm0    ; save z
        pfmul       mm0, mm0    ; z^2
        movd        mm5, [asp0] ; asp0
        pfmul       mm7, mm0    ; asp1 * z^2
        pfadd       mm4, mm0    ; z^2 + asq1 
        pfadd       mm7, mm5    ; asp1 * z^2 + asp0
        movd        mm5, [asq0] ; asq0
        pfmul       mm7, mm0    ; (asp1 * z^2 + asp0) * z^2
        pfmul       mm0, mm4    ; (z^2 + asq1) * z^2
        pfadd       mm0, mm5    ; qx = (z^2 + asq1) * z^2 + asq0
        pfmul       mm7, mm1    ; z^3*px = (asp1 * z^2 + asp0) * z^3
        pfrcp       mm4, mm0    ; 1/qx approx
        pfrcpit1    mm0, mm4    ; 1/qx step 
        movd        mm5, [npio2]; -pi/2
        pfrcpit2    mm0, mm4    ; 1/qx final
        pfmul       mm0, mm7    ; z^3*px/qx
        movq        mm4, mm2    ; z < 0.575 ? 0xfffffff : 0
        pandn       mm2, mm5    ; z < 0.575 ? 0 : -pi/2
        movd        mm5, [pio2] ; pi/2
        movq        mm7, mm4    ; z < 0.575 ? 0xfffffff : 0
        pxor        mm2, mm6    ; z < 0.575 ? 0 : (sign ? pi/2 : -pi/2)
        pfadd       mm1, mm0    ; r = z + z^3*px/qx
        movd        mm0, [oob]  ; special result for out of bound arguments
        pfadd       mm2, mm5    ; z < 0.575 ? pi/2 : (sign ? pi : 0)
        pslld       mm7, 31     ; z < 0.575 ? 0x80000000 : 0
        pandn       mm4, mm1    ; z < 0.575 ? 0 : r
        pxor        mm7, mm6    ; ((z < 0.575) != sign) ? 0x80000000 : 0
        pfadd       mm1, mm4    ; z < 0.575 ? r : 2*r
        pand        mm0, mm3    ; if abs(x) > 1 select special result
        por         mm1, mm7    ; ((z < 0.575) != sign) ? -r,-2*r : r,2*r
        pfadd       mm2, mm1    ; acos(x)
        pandn       mm3, mm2    ; if abs(x) <= 1, select regular result
        por         mm0, mm3    ; mux together results
        ret

_a_acos ENDP



;******************************************************************************
; Routine:  a_asin
; Input:    mm0.lo
; Result:   mm0.lo
; Uses:     mm0-mm7
; Comment:
;   Compute asin(x) using MMX and 3DNow! instructions.Scalar version.
;
;   If the input has an exponent of 0xFF, the result of this routine
;   is undefined. Inputs with an exponent of 0 are treated as true
;   zeroes and return a function value of 0. If the absolute value
;   of the input is greater than 1, a special result is returned
;   (currently this is 0). Results for arguments in [-1, 1] are in
;   [-pi/2, pi/2].
;
;   asin(x)=sign(x)*asin(abs(x)). Let z=abs(x). If z>0.575, asin(z)=
;   pi/2 - 2*asin(sqrt(0.5-0.5*z)). asin(z) for 0 <= z <= 0.575 is
;   is approximated by a rational minimax approximation.
;
;   Testing shows that this function has an error of less than 3.25
;   single precision ulps.
;
;******************************************************************************
ALIGN   32
PUBLIC  _a_asin
_a_asin PROC
        movd        mm6, [sgn]  ; mask for sign bit
        movd        mm7, [mabs] ; mask for absolute value
        movd        mm4, [half] ; 0.5
        pand        mm6, mm0    ; extract sign bit
        movd        mm5, [one]  ; 1.0
        pand        mm0, mm7    ; z = abs(x)
        movq        mm3, mm0    ; z
        pcmpgtd     mm3, mm5    ; z > 1.0 ? 0xFFFFFFFF : 0
        movq        mm5, mm0    ; save z
        pfmul       mm0, mm4    ; z*0.5
        movd        mm2, [bnd]  ; 0.575
        pfsubr      mm0, mm4    ; 0.5 - z * 0.5
        pfrsqrt     mm7, mm0    ; 1/sqrt((1-z)/2) approx
        movq        mm1, mm7    ; complete
        pfmul       mm7, mm7    ;  reciprocal
        pcmpgtd     mm2, mm5    ; z < 0.575 ? 0xfffffff : 0
        pfrsqit1    mm7, mm0    ;   square root
        movd        mm4, [asq1] ; asq1
        pfrcpit2    mm7, mm1    ;    computation
        pfmul       mm7, mm0    ; sqrt((1-z)/2)
        movq        mm0, mm2    ; duplicate mask
        pand        mm5, mm2    ; z < 0.575 ? z : 0
        pandn       mm0, mm7    ; z < 0.575 ? 0 : sqrt((1-z)/2)
        movd        mm7, [asp1] ; asp1
        por         mm0, mm5    ; z < 0.575 ? z : sqrt((1-z)/2)
        movq        mm1, mm0    ; save z
        pfmul       mm0, mm0    ; z^2
        movd        mm5, [asp0] ; asp0
        pfmul       mm7, mm0    ; asp1 * z^2
        pfadd       mm4, mm0    ; z^2 + asq1 
        pfadd       mm7, mm5    ; asp1 * z^2 + asp0
        movd        mm5, [asq0] ; asq0
        pfmul       mm7, mm0    ; (asp1 * z^2 + asp0) * z^2
        pfmul       mm0, mm4    ; (z^2 + asq1) * z^2
        pfadd       mm0, mm5    ; qx = (z^2 + asq1) * z^2 + asq0
        pfmul       mm7, mm1    ; z^3*px = (asp1 * z^2 + asp0) * z^3
        pfrcp       mm4, mm0    ; 1/qx approx
        pfrcpit1    mm0, mm4    ; 1/qx step 
        pfrcpit2    mm0, mm4    ; 1/qx final
        movd        mm4, [pio2] ; pi/2
        pfmul       mm7, mm0    ; z^3*px/qx
        movd        mm0, [oob]  ; special out-of-bounds result
        pfadd       mm1, mm7    ; r = z + z^3*px/qx
        movq        mm5, mm1    ; save r
        pfadd       mm1, mm1    ; 2*r
        pfsubr      mm1, mm4    ; pi/2 - 2*r
        pand        mm5, mm2    ; z < 0.575 ? r : 0
        pandn       mm2, mm1    ; z < 0.575 ? 0 : pi/2 - 2 * r
        pand        mm0, mm3    ; select special result if abs(x) > 1
        por         mm2, mm5    ; z < 0.575 ? r : pi/2 - 2 * r
        por         mm2, mm6    ; asin(x)=sign(x)*(z < 0.575 ? r : pi/2 - 2 * r)
        pandn       mm3, mm2    ; select regular result if abs(x) <= 1
        por         mm0, mm3    ; mux results together
        ret

_a_asin ENDP



;******************************************************************************
; Routine:  a_log
; Input:    mm0.lo
; Result:   mm0.lo
; Uses:     mm0-mm7
; Comment:
;   Compute log(abs(x)) using MMX and 3DNow! instructions. Scalar version.
;
;   If the input has an exponent of 0xFF, the result of this routine
;   is undefined. Inputs with an exponent of 0 are treated as true
;   zeros and return a result of (- max_normal). Underflow or over-
;   flow can not occur otherwise.
;
;   The input x = 2^k * m, thus the natural logarithm is log(2^k) +
;   log(m) = k*log(2) + log(m). Here, m is chosen such than m is <
;   sqrt(2). Then, log(m) = 2*artanh(m+1)/(m-1). A polynomial minimax
;   approximation is used to compute artanh(z). k*log(2) is computed
;   with increased precision by splitting the constant log(2) into a
;   16-bit high-order part and a 24-bit low-order part. The product
;   of the high-order part and k is exactly representable.
;
;   Testing shows that this function has an error of less than 2.42
;   single precision ulps.
;
;******************************************************************************
ALIGN   32
PUBLIC  _a_log
_a_log  PROC
        movd        mm6, [mant] ; mask for mantissa                  
        movq        mm4, mm0    ; save x                            
        movd        mm2, [expo] ; mask for exponent      
        pand        mm0, mm6    ; extract mantissa of x => m 
        movd        mm3, [one]  ; 1.0                            
        pand        mm4, mm2    ; extract biased exponent of x => e 
        por         mm0, mm3    ; float(m)                            
        movd        mm3, [rt2]  ; sqrt(2)                             
        psrld       mm4, 23     ; biased exponent e               
        movq        mm2, mm0    ; save m                    
        pxor        mm5, mm5    ; create 0                     
        movd        mm6, [edec] ; 0x0080000                         
        pcmpgtd     mm0, mm3    ; m > sqrt(2) ? 0xFFFFFFFF : 0        
        pcmpeqd     mm5, mm4    ; sel = (e == 0) ? 0xFFFFFFFFL : 0
        psubd       mm4, mm0    ; increment e if m > sqrt(2)          
        movd        mm3, [bias] ; 127                             
        pand        mm0, mm6    ; m > sqrt(2) ? 0x00800000 : 0
        movd        mm6, [one]  ; 1.0                                
        psubd       mm2, mm0    ; if m > sqrt(2),  m = m/2      
        psubd       mm4, mm3    ; true exponent = i                  
        movq        mm0, mm2    ; save m                             
        pfadd       mm2, mm6    ; m + 1
        pfsub       mm0, mm6    ; m - 1                          
        pi2fd       mm4, mm4    ; float(i)
        movd        mm7, [ln2lo]; lower 24 bits of ln(2)
        pfrcp       mm6, mm2    ; approx 1/mm+1) lo
        movd        mm3, [ln2hi]; upper 16 bits of ln(2)
        pfrcpit1    mm2, mm6    ; refine 1/mm+1) 
        pfmul       mm7, mm4    ; i*ln2lo
        pfmul       mm3, mm4    ; i*ln2hi
        movd        mm4, [c2]   ; c2             
        pfrcpit2    mm2, mm6    ; 1/mm+1)        
        movd        mm1, [c1]   ; c1        
        pfmul       mm2, mm0    ; z=mm+1)/mm-1)                         
        movq        mm0, mm2    ; save z                            
        pfadd       mm0, mm0    ; 2*z
        pfmul       mm2, mm2    ; z^2                             
        movq        mm6, mm2    ; save z^2                             
        pfmul       mm2, mm4    ; c2 * z^2                          
        movd        mm4, [c0]   ; c0               
        pfadd       mm2, mm1    ; c2 * z^2 + c1        
        pfmul       mm2, mm6    ; (c2 * z^2 + c1) * z^2
        movd        mm1, [maxn] ; maxn (negative largest normal)             
        pfmul       mm6, mm0    ; 2*z^3
        pfadd       mm2, mm4    ; px = (c2 * z^2 + c1) * z^2 + c0
        pfmul       mm2, mm6    ; px*2*z^3
        pfadd       mm2, mm0    ; px*2*z^3+2*z
        movq        mm0, mm5    ; sel                               
        pand        mm5, mm1    ; select largest negative normal if e = 0
        pfadd       mm2, mm7    ; px*2*z^3+2*z+i*ln2lo
        pfadd       mm2, mm3    ; ln(z)=px*2*z^3+2*z+i*ln2lo+i*ln2hi
        pandn       mm0, mm2    ; select regular result if e != 0
        por         mm0, mm5    ; mux in either normal or special result
        ret

_a_log  ENDP


;******************************************************************************
; Routine:  a_log10
; Input:    mm0
; Result:   mm0
; Uses:     mm0-mm7, eax, ecx, edx
; Comment:
;   See a_log for the details of operation, this routine merely
;   converts the result into a log base 10 by way of the mathematical
;   identity log10(x) = ln(x)/ln(10).
;
;   Note that due to register contention/latancy issues, calling
;   _a_log() is not noticeably worse than inlining the function.
;
;******************************************************************************
ALIGN   32
PUBLIC  _a_log10
_a_log10    PROC
        call        _a_log      ; mm0 = ln(x)
        movd        mm1, [rle10]; mm1 = 1/ln(10)
        pfmul       mm0, mm1    ; mm0 = ln(x) / ln(10)
        ret
_a_log10    ENDP



;******************************************************************************
; Routine:  a_exp
; Input:    mm0.lo
; Result:   mm0.lo
; Uses:     mm0-mm7
; Comment:
;  Compute exp(x) using MMX and 3DNow! instructions. Scalar version.
;
;  If the input has an exponent of 0xFF, the result of this routine
;  is undefined. Inputs with an exponent of 0 are treated as true
;  zeroes and return a function value of 1. If the input is less
;  than -126*log(2) the result is flushed to zero; exp(-126*log(2))=
;  2^-126, the smallest normalized single precision number. If the
;  input is >= exp(128*log(2)), the result is clamped to max_norm.
;
;  exp(x) = exp(i*log(2)+z) = exp(z)*2^i, where i = trunc(x/log(2))
;  and z = x-i*log(2), with -log(2) <= z <= log(2). The accurate
;  computation of z is very important in the determination of exp(x)
;  Therefore, log(2) is represented as a set of two floating-point
;  numbers ln2hi and ln2lo, where ln2hi contains the most signifcant
;  16 bits of log(2), and ln2lo the next 24 bits. z is therefore
;  computed as z = ((x-i*ln2hi)-i*ln2lo), where the product i*ln2hi
;  is exactly representable. exp(z) is computed by a Pade type
;  rational minimax approximation, a(z)=2*z*P(z^2)/(Q(z^2)-z*P(z^2))
;
;  Testing shows that this function has an error of less than 1.70
;  single precision ulps.
;
;******************************************************************************
ALIGN   32
PUBLIC  _a_exp
_a_exp  PROC
        movd        mm4, [ooln2]    ; 1/log(2)
        movq        mm6, mm0        ; x
        movd        mm1, [upper]    ; 88.72
        movq        mm5, mm0        ; x
        movd        mm3, [sgn]      ; mask for sign bit
        pfmul       mm4, mm0        ; x/log(2)
        pfcmpge     mm6, mm1        ; sel = (x >= 88.72) ? 0xFFFFFFFFL : 0
        movd        mm1, [half]     ; 0.5
        pand        mm3, mm0        ; sign(x)
        movd        mm2, [lower]    ; -87.34
        por         mm3, mm1        ; sign(x)*0.5
        movd        mm7, [ln2hi]    ; ln2hi
        pfadd       mm4, mm3        ; x/log(2)+sign(x)*0.5
        movd        mm1, [ln2lo]    ; ln2lo
        pf2id       mm4, mm4        ; i=trunc(x/log(2)+sign(x)*0.5)=round(x/log(2))
        pfcmpge     mm5, mm2        ; mask = (x >= -87.34) ? 0xFFFFFFFFL : 0
        pi2fd       mm3, mm4        ; xi = float(i)
        pfmul       mm7, mm3        ; xi*ln2hi
        pfmul       mm1, mm3        ; xi*ln2lo
        movd        mm3, [d0]       ; d0
        pfsub       mm0, mm7        ; x-xi*ln2hi
        movd        mm7, [n1]       ; n1
        pfsub       mm0, mm1        ; z=(x-xi*ln2hi)-xi*ln2lo
        movq        mm1, mm0        ; save z
        pfmul       mm0, mm0        ; compute z^2
        movq        mm2, mm0        ; save z^2
        pfadd       mm0, mm3        ; qx = z^2 + d0
        movq        mm3, mm2        ; save z^2
        pfmul       mm2, mm7        ; n1 * x^2
        movd        mm7, [n0]       ; n0
        pfadd       mm2, mm7        ; n1 * z^2 + n0
        pfmul       mm2, mm1        ; px = (n1 * z^2 + n0) * z
        pfsub       mm0, mm2        ; qx - px
        pfrcp       mm1, mm0        ; approx 1/(qx-px)
        pfrcpit1    mm0, mm1        ; refine 1/(qx-px)
        pfadd       mm2, mm2        ; 2*px
        movd        mm3, [one]      ; 1.0
        pfrcpit2    mm0, mm1        ; 1/(qx-px)
        pslld       mm4, 23         ; i = i << 23
        pfmul       mm2, mm0        ; exp(z)-1 = 2*px / (qx - px)
        movd        mm0, [max]      ; max
        pfadd       mm2, mm3        ; exp(z)
        pand        mm0, mm6        ; if (x >= 88.72) select max norm
        paddd       mm2, mm4        ; exp(z) * 2^i = exp(z)+exp(i*log(2))=exp(x)
        pand        mm2, mm5        ; flush normal result to 0 if x < -87.34
        pandn       mm6, mm2        ; if (x < 88.72) select normal result
        por         mm0, mm2        ; mux together results ==> exp(x)
        ret
_a_exp  ENDP


;******************************************************************************
; Routine:  a_sqrt
; Input:    mm0
; Result:   mm0
; Uses:     mm0-mm2
; Comment:
;   Uses the reciprical square root opcodes to compute a 24-bit square
;   root.
;
;   Actual precision of this routine has not yet been tested.
;
;******************************************************************************
ALIGN   32
PUBLIC  _a_sqrt
_a_sqrt PROC
        pfrsqrt     mm1, mm0        ; mm1 = 1/sqrt(x), first pass                   
        movq        mm2, mm1        ; save initial 1/sqrt(x) for Newton-Raphson   
        pfmul       mm1, mm1        ; compute a new 'x' by squaring sqrt(x)         
        pfrsqit1    mm1, mm0        ; N-R 1 (uses original 'x' and approximated 'x')
        pfrcpit2    mm1, mm2        ; N-R 2 (uses 1/sqrt(x) and result of N-R 1)    
                                    ; mm1 = 1/sqrt(x), iteratively refined          
        pfmul       mm0, mm1        ; sqrt(x) = x/sqrt(x) (mathematically true)     
        ret                         ; result in mm0                                 
_a_sqrt ENDP



;******************************************************************************
; Routine:  a_fabs
; Input:    mm0
; Result:   mm0
; Uses:     mm0
; Comment:
;   Uses the fact that the high bit of an IEEE floating point number is
;   a sign bit.  This routine clears the sign bit, making any input number
;   non-negative.  The precision of the number is not affected.
;
;   Note: it is usually more efficient to simply code the 'pand' instruction
;   inline, but this routine is provided here for completeness.
;
;******************************************************************************
ALIGN   32
PUBLIC  _a_fabs
_a_fabs PROC
        pand        mm0, [sign_mask]; clear sign bit in mm0.lo and mm0.hi
        ret
_a_fabs ENDP



;******************************************************************************
; Routine:  a_ceil
; Input:    mm0
; Result:   mm0
; Uses:     mm0-mm4
; Comment:
;   Returns the smallest whole number that is >= the input value.
;******************************************************************************
ALIGN   32
PUBLIC  _a_ceil
_a_ceil PROC
        pxor        mm4, mm4        ; mm4 = 0:0
        movq        mm3, [sh_masks]
        pf2id       mm2, mm0        ; I = mm2
        movq        mm1, [ones]     ; mm1 = 1:1
        pi2fd       mm2, mm2
        pand        mm3, mm0        ; mm3 = sign bit
        pfsub       mm0, mm2        ; F   = mm0
        pfcmpgt     mm0, mm4        ; mm0 = F > 0.0
        pand        mm0, mm1        ; mm0 = (F > 0) ? 1: 0
        por         mm2, mm3        ; re-assert the sign bit
        por         mm0, mm3        ; add sign bit
        pfadd       mm0, mm2
        ret
_a_ceil ENDP



;******************************************************************************
; Routine:  a_floor
; Input:    mm0
; Result:   mm0
; Uses:     mm0-mm3
; Comment:
;   Returns the largest integer that is <= the input value.
;******************************************************************************
ALIGN   32
PUBLIC  _a_floor
_a_floor    PROC
        pf2id       mm2, mm0    ; I = mm2
        pxor        mm1, mm1    ; mm1 = 0|0
        pi2fd       mm2, mm2
        movq        mm3, mm2    ; I = mm3
        pfsubr      mm2, mm0    ; F = mm0
        pfcmpgt     mm1, mm2    ; is F > I? (result becomes a bit mask)
        movq        mm0, [ones] ; mm0 = 1|1
        pand        mm0, mm1    ; mm0 = F > I ? 1 : 0
        pfsubr      mm0, mm3    ; mm0 = I - (F > I ? 1 : 0)
        ret
_a_floor    ENDP

        

;******************************************************************************
; Routine:  a_frexp
; Input:    mm0 (num:???)
; Result:   mm0 (r:exp)
; Uses:     mm0-mm2
; Comment:
;   Split the number into exponent(exp) and mantissa(r)
;******************************************************************************
ALIGN   32
PUBLIC  _a_frexp
_a_frexp    PROC
        movq        mm2, [smh_masks]
        movq        mm1, mm0
        movq        mm3, [pinfs]

        ; Isolate the mantissa (mm0) and exponent (mm1)
        pand        mm0, mm2
        movq        mm2, [PMOne]
        pand        mm1, mm3
        movq        mm3, [HalfVal]
        por         mm0, mm2
        movq        mm2, [two_126s]
        psrld       mm1, 23
        pfmul       mm0, mm3
        psubd       mm1, mm2

        ;; Pack the two back into the output register
        punpckldq   mm0, mm1
        ret
_a_frexp    ENDP



;******************************************************************************
; Routine:  a_ldexp
; Input:    mm0 = x, mm1 = exp
; Result:   mm0 = x+E(exp)
; Uses:     mm0, mm2, eax, edx
; Comment:
;   Computes x * 2^exp, adding the exponent to the exponent of
;   the input value.
;   This version is scalar (rather than vector)
;******************************************************************************
ALIGN   32
PUBLIC  _a_ldexp
_a_ldexp    PROC
        movq        mm2, mm0            ; save a copy of the input value
        pand        mm0, [sign_mask]    ; remove the sign bit
        psrld       mm0, 23             ; shift out the mantissa
        paddd       mm0, mm1            ; add in the input 'exp'
        movd        eax, mm0            ; prepare to test for overflow
        pand        mm2, [smh_masks]    ; mm2 = sign and mantissa bits only
        mov         edx, eax            ; save a copy of this value
        and         eax, 0ffffff00h     ; Did any bits too large get set?
        jnz         short exception     ; If so, handle the exception case
        pslld       mm0, 23             ; shift exponent back into place
        paddd       mm0, mm2            ; assemble the new exponent and mantissa
        ret              

        ALIGN       32   
exception:
        and         edx, MASKSH         ; underflow?
        pxor        mm0, mm0            ; result = 0
        jnz         short ending        ; if underflow, we're done

        movq        mm0, mm2            ; restore original value
        pand        mm0, [sh_masks]     ; keep its sign bit
        por         mm0, [pinfs]        ; mm0 = (x < 0) ? -Inf: +Inf
ending:
        nop
        ret
_a_ldexp    ENDP



;******************************************************************************
; Routine:  a_modf
; Input:    mm0.lo
; Result:   mm0 (res:res)
; Uses:     mm0,mm1
; Comment:
;   Compute both the signed fractional part and the integral part of the input.
;   Return both packed into mm0.  Note that the "integral" part of the input
;   is not an integer, but rather a float with no fractional component.
;   Both return values will have the same sign.
;
;   Note: Performing a "pfacc mm0,mm0" would result in the same value as was
;   passed to this routine.
;
;******************************************************************************
ALIGN   32
PUBLIC  _a_modf
_a_modf PROC
        pf2id       mm1,mm0     ; convert input to integer
        pi2fd       mm1,mm1     ; I = float (int (x))
        pfsub       mm0,mm1     ; F = F - I
        punpckldq   mm0,mm1     ; mm0 = F:I
        ret
_a_modf ENDP



;******************************************************************************
; Routine:  a_fmod
; Input:    mm0 (x), mm1 (y)
; Result:   mm0
; Uses:     mm0-mm3, eax
; Comment:
;   The fmod function calculates the float remainder of x / y such that
;   x = ? * y + rem, where sign(f) = sign(x), and fabs(f) < fabs(y).
;   The ? represents any integer, indicating that mm0 can be greater than
;   mm1.
;******************************************************************************
ALIGN   32
PUBLIC  _a_fmod
_a_fmod PROC
        movd        eax,mm1
        cmp         eax,0
        jz          short exception

        movq        mm2,mm0     ; mm2 = x
        movq        mm3,mm1     ; mm3 = y
        pfrcp       mm0,mm1     ; 1/y, stage 1
        pfrcpit1    mm1,mm0     ; 1/y, stage 2
        pfrcpit2    mm1,mm0     ; mm1 = 1/y
        pfmul       mm2,mm1     ; mm2 = x / y

        ; This stage is identical to modf() above
        pf2id       mm1,mm2     ; int(x/y)
        pi2fd       mm1,mm1     ; float(int(x/y))
        pfsub       mm2,mm1     ; modf(x/y)

        ; Multiply the fraction by 'y'
        movq        mm0,mm3     ; mm0 = y
        pfmul       mm0,mm2     ; y * modf(x/y)
        ret

        ALIGN       32
exception:
        movq        mm0,[sign_mask]
        ret
_a_fmod ENDP



;******************************************************************************
; Routine:  a_sincos (a_cos)
; Input:    mm0.lo
; Result:   mm0 (cos|sin)
; Uses:     mm0-mm7, eax, ebx, ecx, edx, esi
; Comment:
;   sincos computes both sin and cos simultaneously.
;   Since the cos value is returned in mm0.lo, the "a_cos()" routine
;   is really an alias for a_sincos().  The only difficulty is that
;   a_cos does not unpack its result into both halves of mm0.  Since
;   most usages don't need the vectorization, the instruction has been
;   left out.
;******************************************************************************
ALIGN   32
PUBLIC  _a_sincos, _a_cos
_a_cos:
_a_sincos   PROC
        SINCOSMAC               ; mm0 = cos(x) | sin(x)
        nop                     ; K7 doesn't like branching to a 'ret'
        ret
_a_sincos   ENDP



;******************************************************************************
; Routine:  a_sin
; Input:    mm0.lo
; Result:   mm0 (sin|sin)
; Uses:     mm0-mm7, eax, ebx, ecx, edx, esi
;******************************************************************************
ALIGN   32
PUBLIC  _a_sin
_a_sin  PROC
        SINCOSMAC
        punpckhdq   mm0,mm0     ; select sin value
        ret
_a_sin  ENDP



;******************************************************************************
; Routine:  a_tan
; Input:    mm0.lo
; Result:   mm0 = tan|???
; Uses:     mm0-mm7, eax, ebx, ecx, edx, esi
; Comment:
;   Yet another spawn of the SINCOSMAC macro, a_atan computes the arctangent
;   of its input parameter using the definition  tan(x) = sin(x) / cos(x).
;******************************************************************************
ALIGN   32
PUBLIC  _a_tan
_a_tan  PROC
        SINCOSMAC
        movq        mm1,mm0     ; mm1 = sincos(x)
        pfrcp       mm2,mm0     ; mm2 = 1/cos(x), stage 1
        punpckhdq   mm1,mm1     ; mm1 = sin(x)
        pfrcpit1    mm0,mm2     ; mm0 = 1/cos(x), stage 2
        pfrcpit2    mm0,mm2     ; mm0 = 1/cos(x), stage 3
        pfmul       mm0,mm1     ; tan(x) = sin(x) / cos(x)
        ret
_a_tan  ENDP


;******************************************************************************
; Routine:  a_pow - compute pow(mm0.lo,mm1.lo)
; Input:    mm0.lo - base
;           mm1.lo - exponent
; Result:   stored in mm0.lo
; Uses:     mm0-mm7
; Comment:
;   Compute pow(x,y) using MMX and 3DNow! instructions. Scalar version.
;
;   This routine is an almost perfect replacement for the C library
;   function pow(). The main differences are:
;
;   o If one of the inputs has an exponent of 0xFF, the result of
;     this routine is undefined. Inputs with an exponent of 0 are
;     treated as true zeros.
;   o Flushes underflowed results to 0 and clamps overflowed results
;     to the maximum single precision normal.
;   o No error and different result for certain undefined cases,
;     (e.g. negative x raised to non-integer power y; In particular
;     0 ^ y = 0, for all y).
;
;   This routine uses inline versions of y*log(abs(x)) and 2^x
;   routines which may also be used seperately. It computes pow(x,y)
;   as x^y = 2^y*log2(x)). This is fast, but numerically this is not
;   the optimal method.
;
;   This routine has a worst case accuracy of about 16 bits, but
;   for many arguments the accuracy is significantly better, often
;   19 bits or more.
;
;******************************************************************************
ALIGN   32
PUBLIC  _a_pow
_a_pow   PROC
        movq        mm6, mm1    ; y
        pf2id       mm6, mm6    ; int(y)
        pslld       mm6, 31     ; (int(y)&1)<<31
        pand        mm6, mm0    ; bit<31> = (x<0) && (y&1)

;       Compute y*log2(abs(x)) using MMX and 3DNow! instructions. Scalar version.
;
;       If one of the inputs has an exponent of 0xFF, the result of this
;       routine is undefined. Inputs with an exponent of 0 are treated
;       as true zeros. The following cases occur:
;
;       expo(x) == 0 && expo(y) == 0  --> y*log2(abs(x)) = - max_normal
;       expo(x) == 0 && expo(y) != 0  --> y*log2(abs(x)) = - max_normal
;       expo(x) != 0 && expo(y) == 0  --> y*log2(abs(x)) = 0
;
;       Results whose absolute value is less than min_normal are flushed
;       to zero. Results whose absolute value exceeds max_normal are
;       clamped to +/- max_normal.
;
;       The input x = 2^k * m, thus log2(x) = k + log2mm). log2mm) =
;       log2(e)*logmm). Here, m is chosen such than m is < sqrt(2) and
;       k is ajusted accordingly. Then, logmm) = 2*artanhmm-1)/mm+1). A
;       polynomial minimax approximation is used to compute artanh(z),
;       where z = mm-1)/mm+1)
;
;       Testing shows that this function has an error of less than 3.75
;       single precision ulps.
;
;       input      mm0.lo   argument x
;                  mm1.lo   argument y
;       output     mm0.lo   result y*log2(x)
;       destroys   mm0, mm2, mm3, mm4, mm5, mm7

        movd        mm5, [mant] ; mask for mantissa                  
        movq        mm4, mm0    ; save x                            
        movd        mm2, [expo] ; mask for exponent      
        pand        mm0, mm5    ; extract mantissa of x => m 
        movd        mm3, [one]  ; 1.0                            
        pand        mm4, mm2    ; extract biased exponent of x => e 
        por         mm0, mm3    ; floatmm)                            
        movd        mm3, [rt2]  ; sqrt(2)                             
        psrld       mm4, 23     ; biased exponent e               
        movq        mm2, mm0    ; save m                    
        pxor        mm5, mm5    ; create 0                     
        pcmpgtd     mm0, mm3    ; m > sqrt(2) ? 0xFFFFFFFF : 0        
        pcmpeqd     mm5, mm4    ; sel = (e == 0) ? 0xFFFFFFFFL : 0
        movd        mm3, [edec] ; 0x0080000                         
        psubd       mm4, mm0    ; increment e if m > sqrt(2)          
        pand        mm0, mm3    ; m > sqrt(2) ? 0x00800000 : 0
        movd        mm3, [bias] ; 127                             
        psubd       mm2, mm0    ; if m > sqrt(2),  m = m/2      
        psubd       mm4, mm3    ; true exponent = i                  
        movd        mm3, [one]  ; 1.0                                
        movq        mm0, mm2    ; save m                             
        pfadd       mm2, mm3    ; m + 1                               
        pfsub       mm0, mm3    ; m - 1                          
        movd        mm7, [c2]   ; c2             
        pfrcp       mm3, mm2    ; approx 1/mm+1)                    
        pfrcpit1    mm2, mm3    ; refine 1/mm+1) 
        pi2fd       mm4, mm4    ; float(i)
        pfrcpit2    mm2, mm3    ; 1/mm+1)        
        pfmul       mm0, mm2    ; z=mm-1)/mm+1)
        movq        mm2, mm0    ; save z                            
        pfmul       mm0, mm0    ; z^2                             
        movq        mm3, mm0    ; save z^2                             
        pfmul       mm0, mm7    ; c2 * z^2                          
        movd        mm7, [tl2e] ; 2*log2(e)       
        pfmul       mm2, mm7    ; z * 2 * log2(e)
        movd        mm7, [c1]   ; c1        
        pfadd       mm0, mm7    ; c2 * z^2 + c1        
        movd        mm7, [c0]   ; c0               
        pfmul       mm0, mm3    ; (c2 * z^2 + c1) * z^2
        pfmul       mm3, mm2    ; z^3 * 2 * log2(e)       
        pfadd       mm0, mm7    ; px = (c2 * z^2 + c1) * z^2 + c0
        movd        mm7, [maxn] ; maxn (largest normal)             
        pfmul       mm3, mm0    ; px*z^3*2*log2(e)                 
        movq        mm0, mm5    ; sel                               
        pfadd       mm2, mm3    ; px*z^3*2*log2(e)+z*2*log2(e)         
        pand        mm5, mm7    ; select largest negative normal if e = 0
        pfadd       mm2, mm4    ; log2(x)=px*z^3*2*log2(e)+z*2*log2(e)+i 
        pandn       mm0, mm2    ; select regular result if e != 0
        pfmul       mm0, mm1    ; r = y * log2(x)                     
        por         mm0, mm5    ; mux in either normal or special result 

;       Compute 2^r using MMX and 3DNow! instructions. Scalar version.
;
;       If the input has an exponent of 0xFF, the result of this routine
;       is undefined. Inputs with an exponent of 0 are treated as true
;       zeroes and return a function value of 1. If the input is < -126
;       the result is flushed to zero, as 2^-126 is the smallest normal
;       SP number. If the input is >= 128, the result is clamped to
;       max_norm.
;
;       Testing shows that this function has an error of less than 4 SP
;       ulps, meaning that the accuracy is 22 bits or better.
;
;       2^r = 2^(i+x), where i = trunc(x), and -1 <= x <= 1. Then, 2^r =
;       2^i * 2^x = 2^i * ((2^x-1)+1). 2^x-1 is approximated by a Pade
;       type rational minimax approximation.
;
;       input      mm0.lo   argument r
;       output     mm0.lo   result 2^r
;       destroys   mm0, mm1, mm2, mm3, mm4, mm5, mm7

        pf2id     mm4, mm0   ; i = trunc(r)   
        movq      mm5, mm0   ; r                
        pi2fd     mm1, mm4   ; float(trunc(r))   
        movd      mm3, [q1]  ; q1             
        pfsub     mm0, mm1   ; x = frac(r)    
        movq      mm1, mm0   ; save x           
        pfmul     mm0, mm0   ; compute x^2       
        movd      mm7, [p1]  ; p1             
        movq      mm2, mm0   ; save x^2       
        pfadd     mm0, mm3   ; x^2 + q1       
        movq      mm3, mm2   ; save x^2        
        pfmul     mm2, mm7   ; p1 * x^2        
        movd      mm7, [p0]  ; p0             
        pfmul     mm0, mm3   ; (x^2 + q1) * x^2
        movd      mm3, [q0]  ; q0              
        pfadd     mm2, mm7   ; p1 * x^2 + p0   
        movd      mm7, [two] ; 2.0             
        pfadd     mm0, mm3   ; qx = (x^2 + q1) * x^2 + q0                    
        pfmul     mm2, mm1   ; px = (p1 * x^2 + p0) * x           
        pfsub     mm0, mm2   ; qx - px         
        pfmul     mm2, mm7   ; 2*px              
        pfrcp     mm1, mm0   ; approx 1/(qx-px)
        movd      mm7, [one] ; 1.0                
        pfrcpit1  mm0, mm1   ; refine 1/(qx-px)
        pslld     mm4, 23    ; i = i << 23 (shift into exponent)
        pfrcpit2  mm0, mm1   ; 1/(qx-px)                            
        movd      mm3, [mine]; mine                                 
        pfmul     mm2, mm0   ; 2xm1 = 2*px / (qx - px)
        movd      mm1, [maxe]; maxe                              
        pfadd     mm2, mm7   ; 2^x                                
        movq      mm0, mm5   ; r
        pfcmpge   mm5, mm3   ; mask = (r >= -126) ? 0xFFFFFFFFL : 0
        pfcmpge   mm0, mm1   ; sel = (r >= 128) ? 0xFFFFFFFFL : 0
        movd      mm1, [max] ; max
        paddd     mm4, mm2   ; 2^x * 2^i = 2^(x+i)
        pand      mm1, mm0   ; if (r >= 128) select max norm
        pand      mm5, mm4   ; flush normal result to 0 if r < -126
        pandn     mm0, mm5   ; if (r < 128) select normal result
        por       mm0, mm1   ; mux together result                 
     
;       Here we basically have pow(x,y). But in case y is an odd integer
;       and x is negative, the sign bit is wrong. Correct it here using
;       a mask we constructed when we entered pow() based on the values
;       of x and y.
                                
        pxor      mm0, mm6   ; invert sign if ((x<0) && (y&1)) ==> pow(x,y)
        ret
_a_pow  ENDP

_TEXT   ENDS

        END
