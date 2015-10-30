function [ vecs, lambdas ] = DeflationInverse( A, nbr_val_propre )
k = 5000;

vecs = cell(nbr_val_propre,1);
lambdas = zeros(nbr_val_propre, 1);

Z = inv(A);

for i=1:nbr_val_propre
    [v, lambda_v] = PuissancesIterees(Z, k);
    [u, truc] = PuissancesIterees(Z', k);
    
    Z = Z - lambda_v * (v * u') / (u' * v);
    
    lambdas(i) = 1/lambda_v;
    vecs{i} = v;
end
