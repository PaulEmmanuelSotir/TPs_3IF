width = 15;
height = 10;
fente_pos_y = 6;
fente_pos_x = 7;
fente_width = 2;
DotNum = width*height;
nbr_val_propre_sup = 10;
nbr_val_propre_inf = 10;

X = ones(DotNum, 1);

% Bords horizontaux
Tamb(1:fente_pos_x) = 0;
Tamb(fente_pos_x+fente_width:width) = 0;
Tamb(DotNum-width+1:DotNum) = 0;

% Bords verticaux
for i=1:height
   Tamb((i-1)*width+1) = 0;
   Tamb(i*width) = 0;
end

% Fente au milieur du tambour
for i=1:fente_pos_y
   Tamb((i-1)*width+fente_pos_x) = 0;
   Tamb((i-1)*width+fente_pos_x+1) = 0;
   Tamb((i-1)*width+fente_pos_x+2) = 0;
end

% Construit la matrice A représentant l'application du laplacien sur les points inerieurs au tambour
A = zeros(DotNum, DotNum);
for n=1:DotNum
	if Tamb(n) == 1
        % 4-neighbors
        A(n, n) = -4;
        A(n, n+1) = 1;
        A(n, n-1) = 1;
        A(n, n+width) = 1;
        A(n, n-width) = 1;
    else
        A(n,n)=1;
    end
end

% Determine les 10 valeurs propres les plus grandes et plus petites de la matrice A. Ces valeurs propres, au signe près, correspondent aux fréquences de résonnace du tambour (harmoniques).
[max_vecs, max_lambdas] = Deflation(A, nbr_val_propre_sup);
[min_vecs, min_lambdas] = DeflationInverse(A, nbr_val_propre_inf);

% Affiche une animation montrant sucessivement les vecteur propres (vibration) associés aux fréquences determinée précédament.
it = 2;
while it ~= 0
    it = it - 1;
    figure(1);
    for i=1:10
        surf(reshape(max_vecs{i}, 15, 10))
    end
    
end


