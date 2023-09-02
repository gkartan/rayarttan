/////Etat classe : EN COURS
#ifndef _KD_TREE_H_
#define _KD_TREE_H_

#include <vector>
#include "Photon.h"
#include "TraceService.h"

class CPhoton;

class CKDTree 
{

	//construction
public:
	inline CKDTree();
	inline ~CKDTree();

  //operations
  inline void Init(std::vector<CPhoton *> &P);
  inline void Balance(std::vector<CPhoton *> &P, int depth, int index);

  //attributes
public:
	std::vector<CPhoton *> m_Tree;

  //private operations
private:
  inline CPhoton *FindMedian(const std::vector<CPhoton *> &P, int n, int dim);
  inline bool	  Equal(float left, float right);
  inline bool	  GreaterFunc(CVector &left, CVector &right, int dim);
  inline bool	  LessFunc(CVector &left, CVector &right, int dim);
  inline bool	  ApxEqual(float x, float y);
};

//**********************************************************************
// implémentation classe CKDTree
//**********************************************************************
CKDTree::CKDTree()
{
}

CKDTree::~CKDTree()
{
	std::vector<CPhoton*>::iterator k;
	for (k=m_Tree.begin();k!=m_Tree.end();k++) 
	{
		delete (*k);
	}
	m_Tree.clear();
}

void CKDTree::Init(std::vector<CPhoton *> &photonlist)
{
  // calculate space for balanced kdtree
  int depth = log(photonlist.size())/log(2);
  depth++;	//arrondi à la valeur supérieure

  _TRACE_INFO(_STR("Depth %d",depth));
	
  int size=0;
  for (int i=0;i<=depth;i++) size+=pow(2,i);

  m_Tree.resize(size,NULL);
  if(!photonlist.empty())
	Balance(photonlist,0,0);
}

//Calcul de l'équilibrage de l'arbre
void CKDTree::Balance(std::vector<CPhoton *> &P, int depth, int index)
{
  _TRACE_INFO(_STR("Balance - Depth %d - Index %d",depth,index));

  float minx, maxx, miny, maxy, minz, maxz;
  std::vector<CPhoton *>::iterator i;

  i = P.begin();

  // find cube surrounding the points
  minx = (*i)->Position.m_Value[0];  maxx = (*i)->Position.m_Value[0];
  miny = (*i)->Position.m_Value[1];  maxy = (*i)->Position.m_Value[1];
  minz = (*i)->Position.m_Value[2];  maxz = (*i)->Position.m_Value[2];

  for (i = P.begin(); i != P.end(); i++){
    if ((*i)->Position.m_Value[0] < minx)
      minx = (*i)->Position.m_Value[0];
    if ((*i)->Position.m_Value[0] > maxx)
      maxx = (*i)->Position.m_Value[0];
    if ((*i)->Position.m_Value[1] < miny)
      miny = (*i)->Position.m_Value[1];
    if ((*i)->Position.m_Value[1] > maxy)
      maxy = (*i)->Position.m_Value[1];
    if ((*i)->Position.m_Value[2] < minz)
      minz = (*i)->Position.m_Value[2];
    if ((*i)->Position.m_Value[2] >  maxz)
      maxz = (*i)->Position.m_Value[2];
  }

  float distx = maxx - minx;
  float disty = maxy - miny;
  float distz = maxz - minz;

  // find splitplane axis
  int dim = -1;
  if (distx > disty && distx > distz )
    dim = 0;
  else if (disty > distx && disty > distz)
    dim = 1;
  else
    dim = 2;

  CPhoton *median = FindMedian(P,P.size(),dim);

  std::vector<CPhoton *> S1;
  std::vector<CPhoton *> S2;
  std::vector<CPhoton *> eq;
  
  // divide pointset into 2 equally big sets
  for (i = P.begin(); i != P.end() ; i++)
  {
    if ((*i)->Position.m_Value[dim] < median->Position.m_Value[dim])
      S1.push_back((*i));
    else if((*i)->Position.m_Value[dim] > median->Position.m_Value[dim])
      S2.push_back((*i));
    else if (!((ApxEqual((*i)->Position.m_Value[0], median->Position.m_Value[0])) &&
	       (ApxEqual((*i)->Position.m_Value[1], median->Position.m_Value[1])) &&
	       (ApxEqual((*i)->Position.m_Value[2], median->Position.m_Value[2])))) 
      eq.push_back((*i));
  }
  
  for (i = eq.begin(); i != eq.end(); i++){
    if (S1.size() < S2.size())
      S1.push_back((*i));
    else
      S2.push_back((*i));
  }

  median->Flag = dim;
  m_Tree[index] = median;
  // balance left and right part of the tree
  if (!S1.empty()) Balance(S1, depth + 1, 2 * index + 1);
  if (!S2.empty()) Balance(S2, depth + 1, 2 * index + 2);
}



CPhoton *CKDTree::FindMedian(const std::vector<CPhoton *> &P, int n, int dim)
{
    int i, less, greater, equal;
    CPhoton  min, max, guess,maxltguess, mingtguess;
    
    min = max = (*P[0]);
    for (i = 1 ; i < n ; i++) {
      if (P[i]->Position.m_Value[dim] < min.Position.m_Value[dim]) min = *P[i];
        if (P[i]->Position.m_Value[dim] > max.Position.m_Value[dim]) max = *P[i];
    }
    
    while (1) {
	guess.Position = (min.Position + max.Position)/2;
	guess.Power = (min.Power + max.Power)/2;
	guess.Direction = (min.Direction + max.Direction)/2;

	less = 0; greater = 0; equal = 0;
        maxltguess = min;
        mingtguess = max;
        for (i = 0; i < n; i++) {
  	  if (P[i]->Position.m_Value[dim] < guess.Position.m_Value[dim]) {
	    less++;
	    if (P[i]->Position.m_Value[dim] > maxltguess.Position.m_Value[dim]){
	      maxltguess = *P[i]; 
	    }
	  } else if (P[i]->Position.m_Value[dim] > guess.Position.m_Value[dim]) {
	    greater++;
	    if (P[i]->Position.m_Value[dim] < mingtguess.Position.m_Value[dim])
	      mingtguess = *P[i];
	  } else equal++;
        }
	
      
        if (less <= (n + 1) / 2 && greater <= (n + 1) / 2) break ; 
        else if (less > greater) max = maxltguess;
        else min = mingtguess;
    }

    CPhoton *rval = new CPhoton;  
    if (less >= (n + 1)/2) *rval = maxltguess;
    else if (less + equal >= (n + 1) / 2) *rval = guess;
    else *rval = mingtguess;

    return rval;
}


//**********************************************************************
//**Fonctions utilisées dans la classe CKDTree
///Test d'égalité de 2 float
//**********************************************************************
bool CKDTree::Equal(float left, float right)
{
  if (fabs(left - right) < 0.000001)
    return true;

  return false;
}

///Test de grandeur
bool CKDTree::GreaterFunc(CVector &left, CVector &right, int dim)
{

  if (!Equal(left[dim], right[dim]))
    return (left[dim] > right[dim]);

  else if (!Equal(left[(dim + 1) % 3], right[(dim + 1) % 3]))
    return (left[(dim + 1) % 3] > right[(dim + 1) % 3]);
  
  else if (!Equal(left[(dim + 2) % 3], right[(dim + 2) % 3]))
    return (left[(dim + 2) % 3] > right[(dim + 2) % 3]);
    
  else {
    return false;
  }
    
  return false;
}

bool CKDTree::LessFunc(CVector &left, CVector &right, int dim)
{
  
  if (!Equal(left[dim], right[dim])){
    return (left[dim] < right[dim]); 
  }
  else if (!Equal(left[(dim + 1) % 3], right[(dim + 1) % 3])){
    return (left[(dim + 1) % 3] < right[(dim + 1) % 3]);
  }
  else if (!Equal(left[(dim + 2) % 3], right[(dim + 2) % 3])){
    return (left[(dim + 2) % 3] < right[(dim + 2) % 3]);
  }    
  else {
    return false;
  }
    
  return false;
}

bool CKDTree::ApxEqual(float x, float y)
{
  float fconst = 0.01f;
  if (fabs(x-y)<fconst) return true;
  else return false;
}

//**********************************************************************
// Fin implémentation fonctions
//**********************************************************************

#endif // _KD_TREE_H_
