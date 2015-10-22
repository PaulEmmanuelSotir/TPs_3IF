function [vec,lambda] = PuissancesIterees(A,k_max)

// Output variables initialisation (not found in input variables)
vec=[];
lambda=[];

// Display mode
mode(0);

// Display warning for floating point exception
ieee(1);

n = size(A,1);
Y = rand(n,1);

for k = mtlb_imp(0,k_max)
  X = Y/norm(Y);
  Y = A*X;
end;

vec = Y/norm(Y);
lambda = norm(Y);
if sign(lambda*Y)~=sign(A*Y) then
  lambda = lambda*(-1);

end;
endfunction

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








im = imread("D:\Programation\TPs_3IF\TP1_Linear system\lake.jpg");
im = double(rgb2gray(im));
//imshow(uint8(im));

Q1 = im' * im;
Q2 = im * im';

n = size(Q1, 1);
m = size(im, 1);

for k=50:rank(Q1)
    // Compression de l'image
    // deterrmine les k veteurs propres et les k valeurs propres de Q1 (V et Lambdas) les plus grandes
    [V, Lambdas] = Deflation(Q1, k);
    // deterrmine les k veteurs propres de Q2 (V) associés aux k vp les plus grandes
    [U, Lambdas2] = Deflation(Q2, k);
    
    // U, V et Lambdas permettent de reconstituer l'image. Le niveau de compression
    // est choisit en éliminant les plus petites valeur propres (et vecteurs propre associés)
    // L'image compréssée est donc représentée par U, V et Lambdas de dimentations k
    
    // Décompression de l'image
    DecompressedIm = zeros(m, n);
    for i=1:k
        DecompressedIm = DecompressedIm + sqrt(abs(Lambdas(i))) * U(1).entries * V(1).entries';
    end
    
    imshow(uint8(DecompressedIm));
end
