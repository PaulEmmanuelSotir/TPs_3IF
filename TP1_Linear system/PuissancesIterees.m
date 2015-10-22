function [ vec, lambda ] = PuissancesIterees( A, k_max )
n = size(A, 1);
Y = rand(n,1);

% On fait tendre Y vers un vecteur propre de la vp la plus grande en valeur absolue (puissance itérée)
for k=0:k_max
    X = Y/norm(Y); % La normalisation évite d'obtenir des valeurs trop grandes (multiplication de l'ordre de la valeur propre à chaque itérations)
    Y = A*X;
end

vec = Y/norm(Y);
lambda = norm(Y);

% Determine le signe de la valeur propre
if sign(lambda * Y) ~= sign(A*Y)
    lambda = lambda * (-1);

end
