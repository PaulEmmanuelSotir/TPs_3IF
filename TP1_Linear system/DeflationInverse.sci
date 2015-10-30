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
