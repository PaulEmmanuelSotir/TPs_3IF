function [vecs,lambdas] = Deflation(A,nbr_val_propre)

// Output variables initialisation (not found in input variables)
vecs=[];
lambdas=[];

// Display mode
mode(0);

// Display warning for floating point exception
ieee(1);

k = 30;

// ! L.4: real(nbr_val_propre) may be replaced by:
// !    --> nbr_val_propre if nbr_val_propre is Real.
vecs = cell(real(nbr_val_propre),1);
lambdas = zeros(nbr_val_propre,1);

for i = mtlb_imp(1,nbr_val_propre)
  [v,lambda_v] = PuissancesIterees(A,k);
  [u,truc] = PuissancesIterees(mtlb_t(A),k);

  A = mtlb_s(A,(lambda_v*(v*u'))/(u'*v));

  lambdas = mtlb_i(lambdas,i,lambda_v);
  vecs(i).entries = v;
end;
endfunction

function [vecs,lambdas] = DeflationInverse(A,nbr_val_propre)

// Output variables initialisation (not found in input variables)
vecs=[];
lambdas=[];

// Display mode
mode(0);

// Display warning for floating point exception
ieee(1);

k = 5000;

// ! L.4: real(nbr_val_propre) may be replaced by:
// !    --> nbr_val_propre if nbr_val_propre is Real.
vecs = cell(real(nbr_val_propre),1);
lambdas = zeros(nbr_val_propre,1);

Z = inv(A);

for i = mtlb_imp(1,nbr_val_propre)
  [v,lambda_v] = PuissancesIterees(Z,k);
  [u,truc] = PuissancesIterees(Z',k);

  Z = mtlb_s(Z,(lambda_v*(v*u'))/(u'*v));

  lambdas = mtlb_i(lambdas,i,1/lambda_v);
  vecs(i).entries = v;
end;
endfunction


// Display mode
mode(0);

// Display warning for floating point exception
ieee(1);

width = 15;
height = 10;
fente_pos_y = 6;
fente_pos_x = 7;
fente_width = 2;
DotNum = width*height;
nbr_val_propre_sup = 10;
nbr_val_propre_inf = 10;

X = ones(DotNum,1);
X = mtlb_i(X,1:fente_pos_x,0);
X = mtlb_i(X,fente_pos_x+fente_width:width,0);
X = mtlb_i(X,DotNum-width+1:DotNum,0);

for i = 1:height
  X = mtlb_i(X,(i-1)*width+1,0);
  X = mtlb_i(X,i*width,0);
end;

for i = 1:fente_pos_y
  X = mtlb_i(X,(i-1)*width+fente_pos_x,0);
  X = mtlb_i(X,(i-1)*width+fente_pos_x+1,-1);
  X = mtlb_i(X,(i-1)*width+fente_pos_x+2,0);
end;

X = mtlb_i(X,(fente_pos_y-1)*width+fente_pos_x+1,0);

A = zeros(DotNum,DotNum);
for n = 1:DotNum
  if X(n)==1 then
    // 4-neighbors
    A(n,n) = -4;
    A(n,n+1) = 1;
    A(n,n-1) = 1;
    A(n,n+width) = 1;
    A(n,n-width) = 1;
  else if X(n)==1 then
     A(n,n) = 1;
   else
     A(n,n) = 1;
   end;
  end;
end;

[max_vecs,max_lambdas] = Deflation(A,nbr_val_propre_sup);
[min_vecs,min_lambdas] = DeflationInverse(A,nbr_val_propre_inf);

it = 2;
while it~=0
  it = it-1;
  // !! L.51: Matlab function figure not yet converted, original calling sequence used.
  // L.51: (Warning name conflict: function name changed from figure to %figure).
  figure(1);
  for i = 1:10
    // ! L.53: reshape(mtlb_double(max_vecs(i).entries),15,10) may be replaced by:
    // !    --> reshape(max_vecs(i).entries,15,10) if max_vecs(i).entries is not a character string matrix.
    // !! L.53: WARNING: Matlab reshape() suppresses singleton higher dimension, it is not the case for matrix.
    surf(matrix(mtlb_double(min_vecs(i).entries),15,10))
    sleep(550);
  end;
    sleep(1000);
end;
