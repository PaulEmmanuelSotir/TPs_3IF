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
