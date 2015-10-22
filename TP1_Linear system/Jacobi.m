function [ X, m, error ] = Jacobi( A, B, X, max_it)
%JACOBI Resolve linear system AX=B
%   Résolution de systemes linaires avec la methode de Jacobi.

if nargin < 5
    max_it = -1; % no maximum iteration number by default
end

m = 0;
n = size(B, 1);

while(~isequal(A*X,B) && (m < max_it || max_it < 0))
    m = m + 1;
    X_m = X;
    for i=1:n
	
		% Calcul d'une valeur de -N*X
        sum = 0;
        for j=1:n
            if(j ~= i)
                sum = sum + A(i,j)*X_m(j);
            end
        end
		
        X(i) = (B(i) - sum)/A(i,i); % X = Dinv*N*X + Dinv*B
		% (1/A(i,i) sont les valeurs de Dinv et -sum celles de N*X)
    end
end

error = A*X - B;
end