#include "Interaction.h"
#include "pidata.h"


///////////////////////////////////////////////////////////
void NData::setMetropolis()
{                             
static const double    E[]={    0,  335,  410,  510,  660,  840, 1160, 1780, 3900,1e300};
static const double  sii[]={ 24.5, 24.5, 26.4, 30.4, 41.2, 47.2, 48.0, 44.2, 41.0, 41.0};
static const double  sij[]={ 33.0, 33.0, 34.0, 35.1, 36.5, 37.9, 40.2, 42.7, 42.0, 42.0};
static const double  fii[]={ 0.07, 0.07, 0.20, 0.31, 0.43, 0.58, 0.65, 0.69, 0.69, 0.69};
static const double  fij[]={ 0.04, 0.04, 0.07, 0.15, 0.27, 0.37, 0.36, 0.35, 0.35, 0.35};
static const double  Aii[]={  0.1,  0.1,  0.9,  2.7,  9.0, 14.3, 19.2, 1e99, 1e99, 1e99};
static const double  Aij[]={  2.2,  2.2,  1.8,  2.3,  8.8, 15.0, 29.4, 1e99, 1e99, 1e99}; 
static const double  Bii[]={    0,    0,    0,    0,    0,    0,    0,    0,    0,    0};
static const double  Bij[]={ -1.0, -1.0, -1.1, -0.7, -0.2,  0.0,  0.0,  0.0,  0.0,  0.0};
static const double  fpi[]={ 1.00, 1.00, 1.00, 1.00, 1.00, 0.97, 0.80, 0.44, 0.44, 0.44};
	this->E=E;
	s[0]=sii;  s[1]=sij;
	F[0]=fii;  F[1]=fij;
	A[0]=Aii;  A[1]=Aij;
	B[0]=Bii;  B[1]=Bij;
   Fp[0]=fpi; Fp[1]=fpi;
}

///////////////////////////////////////////////////////////
void NData::setOset()
{   
static const double    E[]={    0,  335,  410,  510,  660,  840, 1160, 1780, 2500,1e300};
static const double  sii[]={ 24.5, 24.5, 26.4, 30.4, 41.2, 47.2, 48.0, 44.2, 41.0, 41.0};
static const double  sij[]={ 33.0, 33.0, 34.0, 35.1, 36.5, 37.9, 40.2, 42.7, 42.0, 42.0};
static const double  fii[]={ 0.07, 0.07, 0.20, 0.31, 0.43, 0.48, 0.51, 0.62, 0.70, 0.70};
static const double  fij[]={ 0.04, 0.04, 0.07, 0.15, 0.37, 0.37, 0.51, 0.55, 0.65, 0.65};
static const double  Aii[]={  0.1,  0.1,  0.9,  2.7,  9.0, 14.3, 19.2, 1e99, 1e99, 1e99};
static const double  Aij[]={  2.2,  2.2,  1.8,  2.3,  8.8, 15.0, 29.4, 1e99, 1e99, 1e99};
static const double  Bii[]={    0,    0,    0,    0,    0,    0,    0,    0,    0,    0};
static const double  Bij[]={ -1.0, -1.0, -1.1, -0.7, -0.2,  0.0,  0.0,  0.0,  0.0,  0.0};
static const double fpii[]={ 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 0.90, 0.73, 0.50, 0.50};
static const double fpij[]={ 1.00, 1.00, 1.00, 1.00, 1.00, 0.87, 0.55, 0.46, 0.30, 0.30}; 
	this->E=E;
	s[0]=sii;  s[1]=sij;
	F[0]=fii;  F[1]=fij;
	A[0]=Aii;  A[1]=Aij;
	B[0]=Bii;  B[1]=Bij;
  Fp[0]=fpii; Fp[1]=fpij;
}

///////////////////////////////////////////////////////////
PiData::PiData(int xs):xsec(xs),Ek(0),ij(0),nE(0),iE(0),aE(0),nD(1),iD(0),aD(0)
{ 
	switch(xs)
	{
	  case 0: setMetropolis();break;
	  case 1: set(pdataA,pdataHE);break;
	  case 2: set(pdataB,pdataHE);break;
	  case 3: set(pdataC,pdataHE);break;
	  default:{ cerr<<"PidData::Pidata(int): unknown xsec code "<<xs<<"."<<endl;
	             exit(29);
			 }
	}	  
}

///////////////////////////////////////////////////////////
void PiData::setMetropolis()
{
static const double     E[] ={    0,   49,   85,  128,  184,  250,  350,  540, 1300, 1e10};//Ek(pi)
static const double   sii[] ={   16,   16,   50,  114,  200,  110,   51,   20,   30,   30};//+p,-n (for .p=avg(+p,-p) == .n=avg(+n,-n)
static const double   sij[] ={   15,   15,   21,   43,   66,   44,   23,   22,   30,   30};//+n,-p
static const double  sabs[] ={   20,   20,   32,   45,   36,   18,    0,    0,    0,    0};//+n,-p (for .p,.n its is 2 x smaller) 
static const double  fxii[] ={ 0.00, 0.00, 0.00, 0.00, 0.03, 0.06, 0.16, 0.30, 0.88, 0.88};//-n,+p fraction inelastic/sii (rest is elastic)
static const double  fxij[] ={ 0.45, 0.45, 0.57, 0.62, 0.64, 0.62, 0.56, 0.58, 0.94, 0.94};//+n,-p fraction inelastic/sij
static const double  fx0 [] ={ 0.42, 0.42, 0.36, 0.36, 0.37, 0.40, 0.50, 0.59, 0.94, 0.94};//.n,.p fraction inelastic/(sii+sij)/2
static const double fceii[] ={    0,    0,    0,    0,    0,    0,    0,    0,    0,    0};// ce/ii - impossible
static const double fceij[] ={ 0.80, 1.00, 1.00, 1.00, 0.95, 0.89, 0.72, 0.51, 0.06, 0.06};// 
static const double  fce0[] ={ 0.80, 1.00, 1.00, 1.00, 0.90, 0.84, 0.67, 0.50, 0.05, 0.05};
static const double   Aii[] ={  2.5,  3.2,  2.2,  1.9,  2.2,  2.6,  3.0,  3.0,  3.0,  3.0};
static const double   Aij[] ={  2.5,  1.1,  1.9,  2.2,  2.2,  2.0,  2.7,  3.0,  3.0,  3.0};
static const double    A0[] ={  3.0,  3.4,  2.1,  1.9,  2.1,  2.5,  3.0,  3.0,  3.0,  3.0};
static const double   Bii[] ={ -3.5, -1.8, -2.1, -1.5, -0.3,  2.0,  4.0,  4.0,  4.0,  4.0};
static const double   Bij[] ={  3.5,  0.8,  0.7,  0.8,  1.0,  1.4,  2.6,  3.6,  4.0,  4.0};
static const double    B0[] ={ -2.0, -1.8, -2.0, -1.4,  0.0,  1.7,  4.0,  4.0,  4.0,  4.0};
static const double   Cii[] ={    0,    0,    0,    0,    0,    0,    0,    0,    0,    0}; 
static const double  Cij1[] ={    0,    0,    0,    0,    0,    0,    0,    0,    0,    0}; 
static const double  Cij2[] ={    0,    0,    0,    0,    0,    0,    0,    0,    0,    0}; 
static const double   C01[] ={    0,    0,    0,    0,    0,    0,    0,    0,    0,    0}; 
static const double   C02[] ={    0,    0,    0,    0,    0,    0,    0,    0,    0,    0}; 
static const double   fpi[] ={ 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 0.98, 0.91, 0.24, 0.24}; // 1 pion production/1 or more pion prod
static const double   f2p[] ={ 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00}; // 2 pion production/2 or more pion prod

       this->E=E; 
	   s[0]=sii;      s[1]=sij;      s[2]=sabs;
	   F[0]=fxii;     F[1]=fxij;     F[2]=fx0;
	  Fc[0]=fceii;   Fc[1]=fceij;   Fc[2]=fce0;
       A[0]=Aii;      A[1]=Aij;      A[2]=A0;
       B[0]=Bii;      B[1]=Bij;      B[2]=B0;
     Cel[0]=Cii;    Cel[1]=Cij1;   Cel[2]=C01;
   Cinel[0]=Cii;  Cinel[1]=Cij2; Cinel[2]=C02;
      Fp[0]=fpi;     Fp[1]=fpi;     Fp[2]=fpi;
        F2p=f2p; 

 nE=10;
 nD=1;
}

void PiData::set(double tab[11][16][26],double tab2[6][29]=pdataHE)
{
static double     E[20];
static const int nE=sizeof(E)/sizeof(E[0])+1;
static const int nD=11;
static double   sii[nE][nD],  sij[nE][nD], sabs[nE][nD];  
static double  fxii[nE][nD], fxij[nE][nD], fx0 [nE][nD]; 
static double fceii[nE][nD],fceij[nE][nD], fce0[nE][nD]; 
static double   Aii[nE][nD],  Aij[nE][nD],   A0[nE][nD]; 
static double   Bii[nE][nD],  Bij[nE][nD],   B0[nE][nD]; 
static double  Cii1[nE][nD],  Cii2[nE][nD];
static double  Cij1[nE][nD], Cij2[nE][nD]; 
static double   C01[nE][nD],  C02[nE][nD]; 
static double  fpii[nE][nD], fpij[nE][nD],  fp0[nE][nD]; 
static double   f2p[nE][nD]; 

    this->nE=nE;
	this->nD=nD; 
	xsec=1;
	maxdens=0.17/(fermi*fermi*fermi);

    this->E=E; 
	   s[0]=sii[0];      s[1]=sij[0];      s[2]=sabs[0];
	   F[0]=fxii[0];     F[1]=fxij[0];     F[2]=fx0[0];
	  Fc[0]=fceii[0];   Fc[1]=fceij[0];   Fc[2]=fce0[0];
       A[0]=Aii[0];      A[1]=Aij[0];      A[2]=A0[0];
       B[0]=Bii[0];      B[1]=Bij[0];      B[2]=B0[0];
     Cel[0]=Cii1[0];    Cel[1]=Cij1[0];   Cel[2]=C01[0];
   Cinel[0]=Cii2[0];  Cinel[1]=Cij2[0]; Cinel[2]=C02[0];
      Fp[0]=fpii[0];     Fp[1]=fpij[0];     Fp[2]=fp0[0];
        F2p=f2p[0]; 
/// Fill with data
int prog=13;
for(int i=0;i<nD;i++)
{
  for(int j=0;j<nE;j++)
    {  
      if(j<prog)
      { int J=j;
// E1 E2 sii1 sii2 sij1 sij2 sabs1 sabs2 fxii fxij fx0 fceii fceij fce0 Aii Aij A0 Bii Bij B0 Cii Cij1 Cij2 C01 C02 fpi0
//  0  1  2     3    4    5    6     7    8     9    10  11    12   13   14  15 16  17  18 19  20  21   22   23 24    25 
   if(i==0) E[j]=tab[0][J][0];
	   sii[j][i]=tab[i][J][2 ];
	   sij[j][i]=tab[i][J][4 ];
	  sabs[j][i]=tab[i][J][6 ];  
	  fxii[j][i]=tab[i][J][8 ]; 
	  fxij[j][i]=tab[i][J][9 ]; 
	  fx0 [j][i]=tab[i][J][10]; 
	 fceii[j][i]=tab[i][J][11]; 
	 fceij[j][i]=tab[i][J][12]; 
	  fce0[j][i]=tab[i][J][13]; 
	   Aii[j][i]=tab[i][J][14]; 
	   Aij[j][i]=tab[i][J][15]; 
	    A0[j][i]=tab[i][J][16]; 
	   Bii[j][i]=tab[i][J][17]; 
	   Bij[j][i]=tab[i][J][18]; 
	    B0[j][i]=tab[i][J][19]; 
	  Cii1[j][i]=tab[i][J][20]; 
	  Cii2[j][i]=tab[i][J][20]; 
	  Cij1[j][i]=tab[i][J][21]; 
	  Cij2[j][i]=tab[i][J][23]; 
	   C01[j][i]=tab[i][J][23]; 
	   C02[j][i]=tab[i][J][24]; 
	   fpii[j][i]=tab[i][J][25]; 
	   fpij[j][i]=tab[i][J][25]; 
	   fp0[j][i]=tab[i][J][25]; 
	   f2p[j][i]=1; 
		   }//if
	  else
	 { int J=min(j-prog,5);	    
		
// E1 E2 sii1 sii2 sij1 sij2 sabs1 sabs2 fxii fxij fx0 fceii fceij fce0 Aii Aij A0 Bii Bij B0 Cii Cij1 Cij2 C01 C02 fpi(ii) fpi(ij) fpi(0) f2pi
//  0  1  2     3    4    5    6     7    8     9    10  11    12   13   14  15 16  17  18 19  20  21   22   23 24    25      26      27    28
  if(i==0)  E[j]=tab2[J][0];
  if (J==0)
  {	   
	   sii[j][i]=tab[i][prog-1][3 ];
	   sij[j][i]=tab[i][prog-1][5 ];
      sabs[j][i]=tab[i][prog-1][7 ];  
  }
  else
  {
  	   sii[j][i]=tab2[J][2 ];
	   sij[j][i]=tab2[J][4 ];
  	  sabs[j][i]=tab2[J][6 ];  
  }
	  fxii[j][i]=tab2[J][8 ]; 
	  fxij[j][i]=tab2[J][9 ]; 
	  fx0 [j][i]=tab2[J][10]; 
	 fceii[j][i]=tab2[J][11]; 
	 fceij[j][i]=tab2[J][12]; 
	  fce0[j][i]=tab2[J][13]; 
	   Aii[j][i]=tab2[J][14]; 
	   Aij[j][i]=tab2[J][15]; 
	    A0[j][i]=tab2[J][16]; 
	   Bii[j][i]=tab2[J][17]; 
	   Bij[j][i]=tab2[J][18]; 
	    B0[j][i]=tab2[J][19]; 
	  Cii1[j][i]=tab2[J][20]; 
	  Cii2[j][i]=tab2[J][20]; 
	  Cij1[j][i]=tab2[J][21]; 
	  Cij2[j][i]=tab2[J][22]; 
	   C01[j][i]=tab2[J][23]; 
	   C02[j][i]=tab2[J][24]; 
	   fpii[j][i]=tab2[J][25]; 
	   fpij[j][i]=tab2[J][26]; 
	   fp0[j][i]=tab2[J][27]; 
	   f2p[j][i]=tab2[J][28]; 
	 } //else
   } //for
  }//for
  E[19]=tab2[5][1];
}


////////////////////////////////////////
// Interaction
////////////////////////////////////////

////////////////////////////////////////
// Public methods
////////////////////////////////////////

void Interaction::total_cross_sections(particle &p1, nucleus &t, interaction_parameters &X)
{
  // Pandharipande & Piper procedure for the in-medium cross section modification (added by JTS)
  X.p2 = t.get_nucleon (p1.r);    // target nucleon (stored in the interaction_parameters)
                                  // note! the further calculations (P&P) are isospin independent,
                                  //       it will be chosen precisely in the interaction itself
  vec vvv = X.p2.v();
  p1.p4().boost2 (vvv);
  X.Ekeff = p1.Ek();              // kinetic energy in the target rest frame
  p1.p4().boost2 (-vvv);

  double dens00 = 0.16/fermi3;
  double Masssa = (938.272+939.56533)/2.0;

  double beta = -116.0*X.dens/dens00;
  double lambda = (3.29 - 0.373*X.dens/dens00)/fermi;
  double effmass1 = Masssa/
  (1 - 2.0*Masssa*beta/lambda/lambda/( 1+p1.momentum2()/lambda/lambda )/( 1+p1.momentum2()/lambda/lambda ) );
  double effmass2 = Masssa/
  (1 - 2.0*Masssa*beta/lambda/lambda/( 1+X.p2.momentum2()/lambda/lambda )/( 1+X.p2.momentum2()/lambda/lambda ) );
  double effmass3 = Masssa/
  (1 - 2.0*Masssa*beta/lambda/lambda
  /( 1+ (p1.momentum2()+ X.p2.momentum2())/2.0/lambda/lambda )
  /( 1+ (p1.momentum2()+ X.p2.momentum2())/2.0/lambda/lambda ) );

  double k1minusk2 = ( p1.p()-X.p2.p() ).length()/Masssa;
  double k1minusk2star = ( 1.0/effmass1*p1.p() - 1.0/effmass2*X.p2.p() ).length(); 

  double mod = k1minusk2/k1minusk2star*effmass3/Masssa; // in-medium modification of the cross section - JTS

  //cout<<"mod_proton  "<<X.dens<<"  "<<p1.momentum()<<"  "<<effmass1<<"  "<<mod<<endl;

  double resc=1;                                        // KN: is that ever used?

  switch (X.pdg)
  {
    case pdg_neutron:
      ND.get_sij (X.Ek,X.xsec_n,X.xsec_p);
      //cout<<"neutron  "<<X.r<<"  "<<X.xsec_n<<"  "<<X.xsec_p<<"  "<<mod<<endl;
      X.xsec_n*=mod;
      X.xsec_p*=mod;
      X.xsec_n*=resc;
      X.xsec_p*=resc;
      if (X.Ek<40)
        X.xsec_p*=0.9;                 // effective Pauli blocking 
      //cout<<"neutron2  "<<X.r<<"  "<<X.xsec_n<<"  "<<X.xsec_p<<"  "<<mod<<endl;
      break;

    case pdg_proton:
      ND.get_sij (X.Ek,X.xsec_p,X.xsec_n);
      //cout<<"proton  "<<X.r<<"  "<<X.xsec_n<<"  "<<X.xsec_p<<"  "<<mod<<endl;
      X.xsec_n*=mod;
      X.xsec_p*=mod;
      X.xsec_n*=resc;
      X.xsec_p*=resc;
      if (X.Ek<40)
        X.xsec_n*=0.9;                 // effective Pauli blocking 
      //cout<<"proton2  "<<X.r<<"  "<<X.xsec_n<<"  "<<X.xsec_p<<"  "<<mod<<endl;
      break;

    default:
    { 
      PD.set_density(X.dens);
      PD.set_Ek(X.Ek);
      double rii=PD.sij(0)*millibarn;
      double rij=PD.sij(1)*millibarn;
      double rabs=PD.sij(2)*millibarn;
      switch(X.pdg)
      {
        case pdg_pi:  
          X.xsec_n = (rii+rij+rabs)/2; //.n 
          X.xsec_p = X.xsec_n;         //.p
          break;
        case pdg_piP: 
          X.xsec_n = rij+rabs;         //+n
          X.xsec_p = rii;              //+p
          break;
        case -pdg_piP:
          X.xsec_n = rii;              //-n
          X.xsec_p = rij+rabs;         //-p
          break;
        default:
          X.xsec_n = X.xsec_p = 0;
      };
    };
  }
}

////////////////////////////////////////

bool Interaction::particle_scattering (particle & p1, nucleus &t, interaction_parameters &X)
{
  t.spectator=NULL;

  X.p2.r = p1.r;          // moves the target nucleon to the position of the interaction
                          // note! in e.g. Local Fermi Gas, the momentum distribution changes with position
                          //       it is assumed that the step is small and it does not change

  if(X.p2.v().length()>=1) 
    cout<<"t.n="<<t.n<<"  t.p="<<t.p<<"   "<<X.p2<<endl;
  assert(X.p2.v().length()<1 && "particle scattering");

  if (frandom () < X.frac_proton)   // X.frac_proton is the probability of interaction on proton
                                    // it has the proton cross section included!!!
                                    // KN: The name is a bit misleading.
    X.p2.set_proton ();
  else
    X.p2.set_neutron ();

  switch (p1.pdg)                   // generate the kinematics
  {
    case pdg_proton:
    case pdg_neutron:
      k1=nucleon_;
      return ND.nucleon_scattering (p1, X.p2 , X.n,  X.p);
    case pdg_pi: 
    case pdg_piP: 
    case -pdg_piP:
      k1=pion_;
      return PD.pion_scattering (p1, X.p2, t, X.n, X.p, X.dens);
    default:
      return 0;
  }
}

////////////////////////////////////////

void Interaction::test ()
{
  // echo (Interaction::test);
  init_genrand (time (NULL));
  particle proton (pdg_proton, mass_proton);
  particle neutron (pdg_pi, mass_pi);
  particle neutron2 (neutron);
  particle proton2 (proton);
  proton.set_momentum (vec (1000, 0, 0));
  neutron.set_momentum (vec (-1000, 0, 0));
  int t[1000];
  for (int i = 0; i < 1000; i++)
  {
    t[i] = 0;
  }
  for (int i = 0; i < 1000000; i++)
  {
    scatterAB (proton, neutron, proton2, neutron2, 100, 0, 0, 0, 0, 0, 0, 0);
    t[int (proton2.y + 1000) / 2]++;
  }
  for (int i = 0; i < 1000; i++)
  {
    cout << i << '\t' << t[i] << endl;
  }
}
