function [ vecs, lambdas ] = Deflation( A, nbr_val_propre )
k = 30;

% Création d'un ensemble de vecteurs et de valeurs propres
vecs = cell(nbr_val_propre,1);
lambdas = zeros(nbr_val_propre, 1);

for i=1:nbr_val_propre
	% On trouve la valeur propre (et son vecteur propre) la plus grande en valeur absolue pour A et sa transposée (puissnace itérée)
    [v, lambda_v] = PuissancesIterees(A, k);
    [u, truc] = PuissancesIterees(A', k);
    
	% Trouve une nouvelle matrice A dont les valeurs propres sont les mêmes, hormis lambda_v (0 à la place) (Déflation de Weilandt)
    A = A - lambda_v * (v * u') / (u' * v);
    
    lambdas(i) = lambda_v;
    vecs{i} = v;
end
