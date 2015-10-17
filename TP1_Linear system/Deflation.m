function [ vecs, lambdas ] = Deflation( A, nbr_val_propre )
k = 30;

vecs = cell(nbr_val_propre,1);
lambdas = zeros(nbr_val_propre, 1);

for i=1:nbr_val_propre
    [v, lambda_v] = PuissancesIterees(A, k);
    [u, ~] = PuissancesIterees(A', k);
    
    A = A - lambda_v * (v * u') / (u' * v);
    
    lambdas(i) = lambda_v;
    vecs{i} = v;
end
end

