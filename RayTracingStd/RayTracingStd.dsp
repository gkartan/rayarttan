# Microsoft Developer Studio Project File - Name="RayTracingStd" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=RayTracingStd - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RayTracingStd.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RayTracingStd.mak" CFG="RayTracingStd - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RayTracingStd - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "RayTracingStd - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "RayTracingStd - Win32 Release No Optim" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""$/RAYARTTAN/Sources/RayTracingStd", BAAAAAAA"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "c:\Projets\Runtime\Release"
# PROP Intermediate_Dir "c:\Projets\IntermediateFiles\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G6 /MT /W3 /Gi /Ot /Oa /Og /Oi /Op /Oy /Ob2 /Gy /I ".\\" /I ".\Specifique" /I "..\reused_objects\utilitaires\traceur\\" /I "..\Parser generator\include\\" /I "../wx2/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_CONSOLE" /D "TRACER_DISABLED" /D "__WXMSW__" /D "_NSCREENSAVER" /D "NOMAIN" /YX"stdafx.h" /FD /I /GA /GF /Gs /Zm200 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 nafxcw.lib wsock32.lib ylmt.lib wx.lib png.lib tiff.lib jpeg.lib zlib.lib vfw32.lib /nologo /subsystem:windows /machine:I386 /out:"c:\Projets\Runtime\Release/RayArtTan.exe" /libpath:"..\parser generator\lib\msdev\\" /libpath:"../wx2/lib"
# SUBTRACT LINK32 /profile /map /debug
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy \projets\runtime\release\rayarttan.exe \temp\rayarttan.exe	copy \projets\runtime\release\rayarttan.exe \winntnew\system32\rayarttan.scr
# End Special Build Tool

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "c:\Projets\Runtime\Debug"
# PROP Intermediate_Dir "c:\Projets\IntermediateFiles\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /G6 /MTd /W3 /Gi /ZI /Od /I "." /I ".\Specifique" /I "..\reused_objects\utilitaires\traceur\\" /I "..\Matrix\mtl-2.1.2-20\\" /I "..\Parser generator\include\\" /I "../wx2/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "YYDEBUG" /D "__WXMSW__" /D "NOMAIN" /YX"stdafx.h" /FD /I /Specifique" /GZ /Zm300 " /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 nafxcwd.lib ylmtd.lib wxd.lib wsock32.lib rpcrt4.lib pngd.lib tiffd.lib jpegd.lib zlibd.lib vfw32.lib /nologo /subsystem:windows /incremental:no /debug /machine:I386 /libpath:".\debug" /libpath:"..\parser generator\lib\msdev\\" /libpath:"../wx2/lib"
# SUBTRACT LINK32 /verbose /profile /force

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "RayTracingStd___Win32_Release_No_Optim"
# PROP BASE Intermediate_Dir "RayTracingStd___Win32_Release_No_Optim"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "c:\Projets\Runtime\ReleaseNoOptim"
# PROP Intermediate_Dir "c:\Projets\IntermediateFiles\ReleaseNoOptim"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /G6 /Gr /MT /W3 /Gm /Gi /Zi /Ot /Oa /Og /Oi /Op /Oy /Ob2 /Gy /I ".\\" /I "..\reused_objects\utilitaires\traceur\\" /I "..\Matrix\mtl-2.1.2-20\\" /I "..\Parser generator\include\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_CONSOLE" /D "TRACER_DISABLED" /YX"stdafx.h" /FD /I /GA /GF /Gs /Zm200 /c
# ADD CPP /nologo /G6 /Gr /MT /W3 /Gm /Gi /Zi /Od /Op /Oy /Ob2 /Gy /I ".\\" /I "..\reused_objects\utilitaires\traceur\\" /I "..\Matrix\mtl-2.1.2-20\\" /I "..\Parser generator\include\\" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_CONSOLE" /D "TRACER_DISABLED" /YX"stdafx.h" /FD /I /GA /GF /Gs /Zm200 /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 nafxcw.lib ylmt.lib /nologo /subsystem:windows /debug /machine:I386 /out:"c:\Projets\Runtime\Release/RayArtTan.exe" /libpath:"..\parser generator\lib\msdev\\"
# SUBTRACT BASE LINK32 /profile /map
# ADD LINK32 nafxcw.lib ylmt.lib /nologo /subsystem:windows /debug /machine:I386 /out:"c:\Projets\Runtime\ReleaseNoOptim/RayArtTan.exe" /libpath:"..\parser generator\lib\msdev\\"
# SUBTRACT LINK32 /profile /map

!ENDIF 

# Begin Target

# Name "RayTracingStd - Win32 Release"
# Name "RayTracingStd - Win32 Debug"
# Name "RayTracingStd - Win32 Release No Optim"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\BaseImage.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseIntersection.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseListIntersection.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseRenderPixel.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

# ADD CPP /YX

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ConfigDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HyperLink.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LicenceDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\outviewView.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

# ADD CPP /YX

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RayTracingStd.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

# ADD CPP /YX

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RayTracingStdDoc.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

# ADD CPP /YX

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RayTracingStdView.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

# ADD CPP /YX

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RegisterDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /Yc"stdafx.h"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

# ADD CPP /YX

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=..\reused_objects\utilitaires\Traceur\traceservice.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Accueil.h
# End Source File
# Begin Source File

SOURCE=.\BaseImage.h
# End Source File
# Begin Source File

SOURCE=.\BaseIntersection.h
# End Source File
# Begin Source File

SOURCE=.\BaseListIntersection.h
# End Source File
# Begin Source File

SOURCE=.\BaseRenderPixel.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ClassicFunctions.h
# End Source File
# Begin Source File

SOURCE=.\ComputeRegisterKey.h
# End Source File
# Begin Source File

SOURCE=.\ConfigDlg.h
# End Source File
# Begin Source File

SOURCE=.\Constants.h
# End Source File
# Begin Source File

SOURCE=.\HyperLink.h
# End Source File
# Begin Source File

SOURCE=.\LicenceDlg.h
# End Source File
# Begin Source File

SOURCE=.\Macros.h
# End Source File
# Begin Source File

SOURCE=.\outviewView.h
# End Source File
# Begin Source File

SOURCE=.\ParserUnDef.h
# End Source File
# Begin Source File

SOURCE=.\RayTracingStd.h
# End Source File
# Begin Source File

SOURCE=.\RayTracingStdDoc.h
# End Source File
# Begin Source File

SOURCE=.\RayTracingStdView.h
# End Source File
# Begin Source File

SOURCE=.\Register.h
# End Source File
# Begin Source File

SOURCE=.\RegisterDlg.h
# End Source File
# Begin Source File

SOURCE=.\Specifique\RenderStructure.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\Structures.h
# End Source File
# Begin Source File

SOURCE=.\TypeDefinitions.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\cursor1.cur
# End Source File
# Begin Source File

SOURCE=.\res\imageloading.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logo_final.bmp
# End Source File
# Begin Source File

SOURCE=.\res\RayTracingStd.ico
# End Source File
# Begin Source File

SOURCE=.\RayTracingStd.rc
# End Source File
# Begin Source File

SOURCE=.\res\RayTracingStd.rc2
# End Source File
# Begin Source File

SOURCE=.\res\RayTracingStdDoc.ico
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# End Group
# Begin Group "Light Files"

# PROP Default_Filter ""
# Begin Group "Model Light Files"

# PROP Default_Filter ""
# Begin Group "Model Light Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseModelLight.cpp
# End Source File
# Begin Source File

SOURCE=.\ModelLightMetallic.cpp
# End Source File
# Begin Source File

SOURCE=.\ModelLightMetallicFresnel.cpp
# End Source File
# End Group
# Begin Group "Model Light Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseModelLight.h
# End Source File
# Begin Source File

SOURCE=.\ModelLightMetallic.h
# End Source File
# Begin Source File

SOURCE=.\ModelLightMetallicFresnel.h
# End Source File
# End Group
# End Group
# Begin Group "Geometry Light Files"

# PROP Default_Filter ""
# Begin Group "Light Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseLight.cpp
# End Source File
# Begin Source File

SOURCE=.\LightAmbient.cpp
# End Source File
# Begin Source File

SOURCE=.\LightPoint.cpp
# End Source File
# Begin Source File

SOURCE=.\LightSpot.cpp
# End Source File
# End Group
# Begin Group "Light Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseLight.h
# End Source File
# Begin Source File

SOURCE=.\FrontalLight.h
# End Source File
# Begin Source File

SOURCE=.\LightAmbient.h
# End Source File
# Begin Source File

SOURCE=.\LightPoint.h
# End Source File
# Begin Source File

SOURCE=.\LightSpot.h
# End Source File
# End Group
# End Group
# End Group
# Begin Group "Object Files"

# PROP Default_Filter ""
# Begin Group "Object Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseGeometry.cpp
# End Source File
# Begin Source File

SOURCE=.\Box.cpp
# End Source File
# Begin Source File

SOURCE=.\Cone.cpp
# End Source File
# Begin Source File

SOURCE=.\Cylinder.cpp
# End Source File
# Begin Source File

SOURCE=.\Plan.cpp
# End Source File
# Begin Source File

SOURCE=.\Sphere.cpp
# End Source File
# Begin Source File

SOURCE=.\Text.cpp
# End Source File
# Begin Source File

SOURCE=.\TextChar.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# SUBTRACT CPP /YX

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\Torus.cpp
# End Source File
# End Group
# Begin Group "Object Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseFractal.h
# End Source File
# Begin Source File

SOURCE=.\BaseGeometry.h
# End Source File
# Begin Source File

SOURCE=.\BaseListGeometry.h
# End Source File
# Begin Source File

SOURCE=.\Box.h
# End Source File
# Begin Source File

SOURCE=.\Cone.h
# End Source File
# Begin Source File

SOURCE=.\Cylinder.h
# End Source File
# Begin Source File

SOURCE=.\Fractal.h
# End Source File
# Begin Source File

SOURCE=.\FractalZ2.h
# End Source File
# Begin Source File

SOURCE=.\FrontalFractal.h
# End Source File
# Begin Source File

SOURCE=.\FrontalGeometry.h
# End Source File
# Begin Source File

SOURCE=.\Plan.h
# End Source File
# Begin Source File

SOURCE=.\Sphere.h
# End Source File
# Begin Source File

SOURCE=.\Text.h
# End Source File
# Begin Source File

SOURCE=.\TextChar.h
# End Source File
# Begin Source File

SOURCE=.\Torus.h
# End Source File
# End Group
# End Group
# Begin Group "Ihm Files"

# PROP Default_Filter ""
# Begin Group "Ihm Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Accueil.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ColorIhm.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CoordIhm.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\EditColorMapDlg.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ihminterface.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\listctrlex.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\QuaterIhm.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RenderingDoc.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RenderingFrame.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RenderingView.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# End Group
# Begin Group "Ihm Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ColorIhm.h
# End Source File
# Begin Source File

SOURCE=.\CoordIhm.h
# End Source File
# Begin Source File

SOURCE=.\EditColorMapDlg.h
# End Source File
# Begin Source File

SOURCE=.\IhmConstants.h
# End Source File
# Begin Source File

SOURCE=.\ihminterface.h
# End Source File
# Begin Source File

SOURCE=.\listctrlex.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\QuaterIhm.h
# End Source File
# Begin Source File

SOURCE=.\RenderingDoc.h
# End Source File
# Begin Source File

SOURCE=.\RenderingFrame.h
# End Source File
# Begin Source File

SOURCE=.\RenderingView.h
# End Source File
# End Group
# End Group
# Begin Group "Rendering"

# PROP Default_Filter ""
# Begin Group "Rendering Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseRender.cpp
# End Source File
# Begin Source File

SOURCE=.\RenderAdaptativeSampling.cpp
# End Source File
# Begin Source File

SOURCE=.\RenderInterface.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /YX

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

# ADD BASE CPP /YX
# ADD CPP /YX

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\RenderStdRayTracing.cpp
# End Source File
# Begin Source File

SOURCE=.\RunRender.cpp
# End Source File
# End Group
# Begin Group "Rendering Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseRender.h
# End Source File
# Begin Source File

SOURCE=.\RenderAdaptativeSampling.h
# End Source File
# Begin Source File

SOURCE=.\RenderInterface.h
# End Source File
# Begin Source File

SOURCE=.\RenderStdRaytracing.h
# End Source File
# Begin Source File

SOURCE=.\RenderType.h
# End Source File
# Begin Source File

SOURCE=.\RunRender.h
# End Source File
# End Group
# End Group
# Begin Group "Matiere Files"

# PROP Default_Filter ""
# Begin Group "Matiere Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseMatiere.cpp
# End Source File
# Begin Source File

SOURCE=.\BaseProcedural.cpp
# End Source File
# Begin Source File

SOURCE=.\ProcGradientMatiere.cpp
# End Source File
# Begin Source File

SOURCE=.\ProcSimpleNoiseMatiere.cpp
# End Source File
# Begin Source File

SOURCE=.\TextureElement.cpp
# End Source File
# End Group
# Begin Group "Matiere Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseMatiere.h
# End Source File
# Begin Source File

SOURCE=.\BaseProcedural.h
# End Source File
# Begin Source File

SOURCE=.\CommonMatiere.h
# End Source File
# Begin Source File

SOURCE=.\FrontalMaterial.h
# End Source File
# Begin Source File

SOURCE=.\ProcGradientMatiere.h
# End Source File
# Begin Source File

SOURCE=.\ProcSimpleNoiseMatiere.h
# End Source File
# Begin Source File

SOURCE=.\TextureElement.h
# End Source File
# End Group
# End Group
# Begin Group "Ray Files"

# PROP Default_Filter ""
# Begin Group "Ray Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Ray.cpp
# End Source File
# Begin Source File

SOURCE=.\RayEye.cpp
# End Source File
# Begin Source File

SOURCE=.\RayLight.cpp
# End Source File
# End Group
# Begin Group "Ray Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Ray.h
# End Source File
# Begin Source File

SOURCE=.\RayEye.h
# End Source File
# Begin Source File

SOURCE=.\RayLight.h
# End Source File
# End Group
# End Group
# Begin Group "Math Files"

# PROP Default_Filter ""
# Begin Group "Polynomial"

# PROP Default_Filter ""
# Begin Group "Polynomial Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseListPolyNomial.cpp
# End Source File
# Begin Source File

SOURCE=.\ListSturmSequence.cpp
# End Source File
# Begin Source File

SOURCE=.\PolyNomial.cpp
# End Source File
# Begin Source File

SOURCE=.\PolyNomialCubic.cpp
# End Source File
# Begin Source File

SOURCE=.\PolyNomialQuadratic.cpp
# End Source File
# Begin Source File

SOURCE=.\PolyNomialQuartic.cpp
# End Source File
# End Group
# Begin Group "Polynomial Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseListPolyNomial.h
# End Source File
# Begin Source File

SOURCE=.\ListSturmSequence.h
# End Source File
# Begin Source File

SOURCE=.\PolyNomial.h
# End Source File
# Begin Source File

SOURCE=.\PolyNomialCubic.h
# End Source File
# Begin Source File

SOURCE=.\PolyNomialQuadratic.h
# End Source File
# Begin Source File

SOURCE=.\PolyNomialQuartic.h
# End Source File
# End Group
# End Group
# Begin Group "Dimensionnal Files"

# PROP Default_Filter ""
# Begin Group "Dimensionnal Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseHyperAlgebra.cpp
# End Source File
# End Group
# Begin Group "Dimensionnal Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseHyperAlgebra.h
# End Source File
# Begin Source File

SOURCE=.\BaseHyperFonction.h
# End Source File
# Begin Source File

SOURCE=.\BaseVector.h
# End Source File
# Begin Source File

SOURCE=.\ComputeExpr.h
# End Source File
# Begin Source File

SOURCE=.\Coord.h
# End Source File
# Begin Source File

SOURCE=.\HyperComplex.h
# End Source File
# Begin Source File

SOURCE=.\HyperComplexExot01.h
# End Source File
# Begin Source File

SOURCE=.\HyperComplexExot02.h
# End Source File
# Begin Source File

SOURCE=.\HyperComplexExot03.h
# End Source File
# Begin Source File

SOURCE=.\HyperComplexExot04.h
# End Source File
# Begin Source File

SOURCE=.\HyperComplexExot05.h
# End Source File
# Begin Source File

SOURCE=.\HyperComplexExot06.h
# End Source File
# Begin Source File

SOURCE=.\HyperComplexExot07.h
# End Source File
# Begin Source File

SOURCE=.\HyperComplexExot08.h
# End Source File
# Begin Source File

SOURCE=.\HyperComplexExot09.h
# End Source File
# Begin Source File

SOURCE=.\HyperComplexExot10.h
# End Source File
# Begin Source File

SOURCE=.\HyperComplexExot11.h
# End Source File
# Begin Source File

SOURCE=.\HyperComplexExot12.h
# End Source File
# Begin Source File

SOURCE=.\HyperComplexExot13.h
# End Source File
# Begin Source File

SOURCE=.\HyperComplexExot14.h
# End Source File
# Begin Source File

SOURCE=.\HyperComplexExot15.h
# End Source File
# Begin Source File

SOURCE=.\HyperComplexExot16.h
# End Source File
# Begin Source File

SOURCE=.\HyperFonctionNormal.h
# End Source File
# Begin Source File

SOURCE=.\ListExpr.h
# End Source File
# Begin Source File

SOURCE=.\Quaternion.h
# End Source File
# Begin Source File

SOURCE=.\Vector.h
# End Source File
# End Group
# End Group
# Begin Group "Derivate"

# PROP Default_Filter ""
# Begin Group "Derivate Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ComputeDerivate.cpp
# End Source File
# Begin Source File

SOURCE=.\DerivateFileParser.cpp
# End Source File
# Begin Source File

SOURCE=.\DerivateFileParser.l.cpp
# End Source File
# Begin Source File

SOURCE=.\FormulaDerivate.cpp
# End Source File
# Begin Source File

SOURCE=.\FormulaDerivate.l.cpp
# End Source File
# End Group
# Begin Group "Derivate Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ComputeDerivate.h
# End Source File
# Begin Source File

SOURCE=.\DerivateFileParser.h
# End Source File
# Begin Source File

SOURCE=.\DerivateFileParser.l.h
# End Source File
# Begin Source File

SOURCE=.\FormulaDerivate.h
# End Source File
# Begin Source File

SOURCE=.\FormulaDerivate.l.h
# End Source File
# Begin Source File

SOURCE=.\RandomFractal.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\DerivateFileParser.l

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

# Begin Custom Build - Building Lexer
InputPath=.\DerivateFileParser.l
InputName=DerivateFileParser

"$(InputName).l.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	alex.exe -mi $(InputName).l -o $(InputName).l.cpp  -Tcpp -i $(InputName).l.h

# End Custom Build

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\DerivateFileParser.y

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

# Begin Custom Build - Building Parser
InputPath=.\DerivateFileParser.y
InputName=DerivateFileParser

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ayacc.exe -mi $(InputName).y -o $(InputName).cpp  -Tcpp -d $(InputName).h -pc

# End Custom Build

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FormulaDerivate.l

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# Begin Custom Build - Building Lexer
InputPath=.\FormulaDerivate.l
InputName=FormulaDerivate

"$(InputName).l.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	alex.exe -mi $(InputName).l -o $(InputName).l.cpp  -Tcpp -l -i $(InputName).l.h

# End Custom Build

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

# Begin Custom Build - Building Lexer
InputPath=.\FormulaDerivate.l
InputName=FormulaDerivate

"$(InputName).l.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	alex.exe -mi $(InputName).l -o $(InputName).l.cpp  -Tcpp -i $(InputName).l.h

# End Custom Build

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

# Begin Custom Build - Building Lexer
InputPath=.\FormulaDerivate.l
InputName=FormulaDerivate

"$(InputName).l.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	alex.exe -mi $(InputName).l -o $(InputName).l.cpp  -Tcpp -l -i $(InputName).l.h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FormulaDerivate.y

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# Begin Custom Build - Building Parser
InputPath=.\FormulaDerivate.y
InputName=FormulaDerivate

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ayacc.exe -mi $(InputName).y -o $(InputName).cpp  -Tcpp -d $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

# Begin Custom Build - Building Parser
InputPath=.\FormulaDerivate.y
InputName=FormulaDerivate

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ayacc.exe -mi $(InputName).y -o $(InputName).cpp  -Tcpp -d $(InputName).h -pc

# End Custom Build

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

# Begin Custom Build - Building Parser
InputPath=.\FormulaDerivate.y
InputName=FormulaDerivate

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ayacc.exe -mi $(InputName).y -o $(InputName).cpp  -Tcpp -d $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Matrix"

# PROP Default_Filter ""
# Begin Group "Matrix Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MatrixTransform.cpp
# End Source File
# End Group
# Begin Group "Matrix Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\MatrixSqr.h
# End Source File
# Begin Source File

SOURCE=.\MatrixTransform.h
# End Source File
# End Group
# End Group
# Begin Group "Functions"

# PROP Default_Filter ""
# Begin Group "Functions Source Files"

# PROP Default_Filter ""
# End Group
# Begin Group "Functions Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Power.h
# End Source File
# Begin Source File

SOURCE=.\Rand.h
# End Source File
# Begin Source File

SOURCE=.\SinC.h
# End Source File
# Begin Source File

SOURCE=.\SinhC.h
# End Source File
# Begin Source File

SOURCE=.\TrigohAMD.h
# End Source File
# End Group
# End Group
# Begin Group "Noise"

# PROP Default_Filter ""
# Begin Group "Noise Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Noise3D.cpp
# End Source File
# Begin Source File

SOURCE=.\Noise3DGranite.cpp
# End Source File
# End Group
# Begin Group "Noise Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Noise3D.h
# End Source File
# Begin Source File

SOURCE=.\Noise3DGranite.h
# End Source File
# End Group
# End Group
# End Group
# Begin Group "Color Files"

# PROP Default_Filter ""
# Begin Group "Color Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Color.cpp
# End Source File
# Begin Source File

SOURCE=.\Dispersion.cpp
# End Source File
# End Group
# Begin Group "Color Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseColor.h
# End Source File
# Begin Source File

SOURCE=.\Color.h
# End Source File
# Begin Source File

SOURCE=.\Dispersion.h
# End Source File
# End Group
# End Group
# Begin Group "FormulaParser"

# PROP Default_Filter ""
# Begin Group "Formula Parser Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FormulaParser.cpp
# End Source File
# Begin Source File

SOURCE=.\FormulaParser.l.cpp
# End Source File
# End Group
# Begin Group "Formula Parser Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FormulaParser.h
# End Source File
# Begin Source File

SOURCE=.\FormulaParser.l.h
# End Source File
# Begin Source File

SOURCE=.\FormulaParserParser.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\FormulaParser.l

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# Begin Custom Build - Building Lexer
InputPath=.\FormulaParser.l
InputName=FormulaParser

"$(InputName).l.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	alex.exe -mi $(InputName).l -o $(InputName).l.cpp  -Tcpp -l -i $(InputName).l.h

# End Custom Build

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

# Begin Custom Build - Building Lexer
InputPath=.\FormulaParser.l
InputName=FormulaParser

"$(InputName).l.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	alex.exe -mi $(InputName).l -o $(InputName).l.cpp  -Tcpp -i $(InputName).l.h

# End Custom Build

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

# Begin Custom Build - Building Lexer
InputPath=.\FormulaParser.l
InputName=FormulaParser

"$(InputName).l.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	alex.exe -mi $(InputName).l -o $(InputName).l.cpp  -Tcpp -l -i $(InputName).l.h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FormulaParser.y

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# Begin Custom Build - Building Parser
InputPath=.\FormulaParser.y
InputName=FormulaParser

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ayacc.exe -mi $(InputName).y -o $(InputName).cpp  -Tcpp -d $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

# Begin Custom Build - Building Parser
InputPath=.\FormulaParser.y
InputName=FormulaParser

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ayacc.exe -mi $(InputName).y -o $(InputName).cpp  -Tcpp -d $(InputName).h -pc

# End Custom Build

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

# Begin Custom Build - Building Parser
InputPath=.\FormulaParser.y
InputName=FormulaParser

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ayacc.exe -mi $(InputName).y -o $(InputName).cpp  -Tcpp -d $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Camera Files"

# PROP Default_Filter ""
# Begin Group "Camera Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseCamera.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

# ADD CPP /Gi-
# SUBTRACT CPP /YX /Yc /Yu

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\CamParalPlane.cpp
# End Source File
# Begin Source File

SOURCE=.\CamPersPlane.cpp
# End Source File
# Begin Source File

SOURCE=.\CamSphere.cpp
# End Source File
# Begin Source File

SOURCE=.\CamSuperEllipsoid.cpp
# End Source File
# End Group
# Begin Group "Camera Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\BaseCamera.h
# End Source File
# Begin Source File

SOURCE=.\CamParalPlane.h
# End Source File
# Begin Source File

SOURCE=.\CamPersPlane.h
# End Source File
# Begin Source File

SOURCE=.\CamSphere.h
# End Source File
# Begin Source File

SOURCE=.\CamSuperEllipsoid.h
# End Source File
# Begin Source File

SOURCE=.\FrontalCamera.h
# End Source File
# End Group
# End Group
# Begin Group "Ihm Page Files"

# PROP Default_Filter ""
# Begin Group "Ihm Page Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CameraPage.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FractalPage.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FractalSheet.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ImagePage.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\LightPage.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TextureGeneralPage.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TextureProceduralPage.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\TextureSheet.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# End Group
# Begin Group "Ihm Page Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CameraPage.h
# End Source File
# Begin Source File

SOURCE=.\FractalPage.h
# End Source File
# Begin Source File

SOURCE=.\FractalSheet.h
# End Source File
# Begin Source File

SOURCE=.\ImagePage.h
# End Source File
# Begin Source File

SOURCE=.\LightPage.h
# End Source File
# Begin Source File

SOURCE=.\TextureGeneralPage.h
# End Source File
# Begin Source File

SOURCE=.\TextureProceduralPage.h
# End Source File
# Begin Source File

SOURCE=.\TextureSheet.h
# End Source File
# End Group
# End Group
# Begin Group "Amd Files"

# PROP Default_Filter ""
# Begin Group "Amd Source Files"

# PROP Default_Filter ""
# End Group
# Begin Group "Amd Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\amath.h
# End Source File
# Begin Source File

SOURCE=.\amd3dx.h
# End Source File
# End Group
# End Group
# Begin Group "Ihm Common"

# PROP Default_Filter ""
# Begin Group "Ihm Common Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\oxbitmapbutton.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\oxcolorpickerbutton.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\oxcolorpickerctrl.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\oxpopupbarctrl.cpp

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# ADD CPP /O1

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

!ENDIF 

# End Source File
# End Group
# Begin Group "Ihm Common Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\oxbitmapbutton.h
# End Source File
# Begin Source File

SOURCE=.\oxbitmapbuttonres.h
# End Source File
# Begin Source File

SOURCE=.\oxcolorpickerbutton.h
# End Source File
# Begin Source File

SOURCE=.\oxcolorpickerctrl.h
# End Source File
# Begin Source File

SOURCE=.\oxpopupbarctrl.h
# End Source File
# End Group
# End Group
# Begin Group "FileParser Files"

# PROP Default_Filter ""
# Begin Group "FileParser Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FileParser.cpp
# End Source File
# Begin Source File

SOURCE=.\FileParser.l.cpp
# End Source File
# End Group
# Begin Group "FileParser Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FileParser.h
# End Source File
# Begin Source File

SOURCE=.\FileParser.l.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\FileParser.l

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# Begin Custom Build - Building Lexer
InputPath=.\FileParser.l
InputName=FileParser

"$(InputName).l.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	alex.exe -mi $(InputName).l -o $(InputName).l.cpp  -Tcpp -l -i $(InputName).l.h

# End Custom Build

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

# Begin Custom Build - Building Lexer
InputPath=.\FileParser.l
InputName=FileParser

"$(InputName).l.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	alex.exe -mi $(InputName).l -o $(InputName).l.cpp  -Tcpp -i $(InputName).l.h

# End Custom Build

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

# Begin Custom Build - Building Lexer
InputPath=.\FileParser.l
InputName=FileParser

"$(InputName).l.cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	alex.exe -mi $(InputName).l -o $(InputName).l.cpp  -Tcpp -l -i $(InputName).l.h

# End Custom Build

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\FileParser.y

!IF  "$(CFG)" == "RayTracingStd - Win32 Release"

# Begin Custom Build - Building Parser
InputPath=.\FileParser.y
InputName=FileParser

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ayacc.exe -mi $(InputName).y -o $(InputName).cpp  -Tcpp -l -d $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Debug"

# Begin Custom Build - Building Parser
InputPath=.\FileParser.y
InputName=FileParser

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ayacc.exe -mi $(InputName).y -o $(InputName).cpp  -Tcpp -d $(InputName).h

# End Custom Build

!ELSEIF  "$(CFG)" == "RayTracingStd - Win32 Release No Optim"

# Begin Custom Build - Building Parser
InputPath=.\FileParser.y
InputName=FileParser

"$(InputName).cpp" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"
	ayacc.exe -mi $(InputName).y -o $(InputName).cpp  -Tcpp -l -d $(InputName).h

# End Custom Build

!ENDIF 

# End Source File
# End Group
# Begin Group "Photon Map Files"

# PROP Default_Filter ""
# Begin Group "Photon Map Source Files"

# PROP Default_Filter ""
# End Group
# Begin Group "Photon Map Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\KDTree.h
# End Source File
# Begin Source File

SOURCE=.\Photon.h
# End Source File
# Begin Source File

SOURCE=.\PhotonTracer.h
# End Source File
# End Group
# End Group
# Begin Group "ScreenSaver Files"

# PROP Default_Filter ""
# Begin Group "ScreenSaver Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\renderingwnd.cpp
# End Source File
# Begin Source File

SOURCE=.\saverwnd.cpp
# End Source File
# Begin Source File

SOURCE=.\ScreenSaverDlg.cpp
# End Source File
# End Group
# Begin Group "ScreenSaver Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\renderingwnd.h
# End Source File
# Begin Source File

SOURCE=.\saverwnd.h
# End Source File
# Begin Source File

SOURCE=.\ScreenSaverDlg.h
# End Source File
# End Group
# End Group
# Begin Group "Text Files"

# PROP Default_Filter ""
# Begin Group "Text Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FontFile.cpp
# End Source File
# Begin Source File

SOURCE=.\FormatGlyph.cpp
# End Source File
# Begin Source File

SOURCE=.\TextFont.cpp
# End Source File
# End Group
# Begin Group "Text Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\FontFile.h
# End Source File
# Begin Source File

SOURCE=.\FormatGlyph.h
# End Source File
# Begin Source File

SOURCE=.\TextFont.h
# End Source File
# Begin Source File

SOURCE=.\TextFontStruct.h
# End Source File
# End Group
# End Group
# Begin Group "Animation Files"

# PROP Default_Filter ""
# Begin Group "Animation Source Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\WRITEAVI.CPP
# End Source File
# End Group
# Begin Group "Animation Header Files"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\WriteAVI.h
# End Source File
# End Group
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
