function [ X, m, error ] = Relax( A, B, X, omega, max_it)
%Relaxed Gauss Resolve linear system AX=B
%   Résolution de systemes linaires avec la methode de Gauss relaxée

if nargin < 5
    max_it = -1; % no maximum iteration number by default
end

m = 0;
n = size(B, 1);

while(~isequal(A*X,B) && (m < max_it || max_it < 0))
	m = m + 1;
	X_m = X;
	for i=1:n
		LX = 0;
		for j=1:i-1
			LX = LX + A(i,j)*X(j);
		end
		UX = 0;
		for j=i+1:n
			UX = UX + A(i,j)*X_m(j);
		end
		
		X(i) = (B(i) - LX - UX)/A(i,i); % (L + D)X = B - U*X_m
		X(i) = (1-omega)*X_m(i)+omega*X(i);	% (omg*L + D)X = omg*B - omg*U*X_m + (1-omg)D*X_m
											% Soit (omg*Dinv*L + 1)X = omg*Dinv*(B - U*X_m) + (1-omg)*X_m
	end
end

error = A*X - B;
end

