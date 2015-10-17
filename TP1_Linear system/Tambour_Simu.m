width = 15;
height = 10;
fente_pos_y = 6;
fente_pos_x = 7;
fente_width = 2;
DotNum = width*height;
nbr_val_propre_sup = 10;
nbr_val_propre_inf = 10;

X = ones(DotNum, 1);
X(1:fente_pos_x) = 0;
X(fente_pos_x+fente_width:width) = 0;
X(DotNum-width+1:DotNum) = 0;

for i=1:height
   X((i-1)*width+1) = 0;
   X(i*width) = 0;
end

for i=1:fente_pos_y
   X((i-1)*width+fente_pos_x) = 0;
   X((i-1)*width+fente_pos_x+1) = -1;
   X((i-1)*width+fente_pos_x+2) = 0;
end

X((fente_pos_y-1)*width + fente_pos_x+1) = 0;

A = zeros(DotNum, DotNum);
for n=1:DotNum
	if X(n) == 1
        % 4-neighbors
        A(n, n) = -4;
        A(n, n+1) = 1;
        A(n, n-1) = 1;
        A(n, n+width) = 1;
        A(n, n-width) = 1;
    else if X(n) == 1
            A(n,n)=1;
        else
            A(n,n)=1;
        end
    end
end

[max_vecs, max_lambdas] = Deflation(A, nbr_val_propre_sup);
[min_vecs, min_lambdas] = DeflationInverse(A, nbr_val_propre_inf);

max_vecs
max_lambdas

min_vecs
min_lambdas
