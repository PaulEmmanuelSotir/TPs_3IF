function [ X, m, error ] = Gauss( A, B, X, max_it )
%GAUSS Resolve linear system AX=B
%   Résolution de systemes linaires avec la methode de Gauss-Seidel

if nargin < 4
    max_it = -1 % no maximum iteration number by default
end

m = 0;
n = size(B, 1);

while(~isequal(A*X,B) && (m < max_it || max_it < 0))
    m = m + 1;
    X_m = X;
    for i=1:n
        sum1 = 0;
        for j=1:i-1
            sum1 = sum1 + A(i,j)*X(j);
        end
        sum2 = 0;
        for j=i+1:n
        	sum2 = sum2 + A(i,j)*X_m(j);% X_m pas nescessaires?
        end
        
        X(i) = (B(i) - sum1 - sum2)/A(i,i);
    end
end

error = A*X - B;
end

