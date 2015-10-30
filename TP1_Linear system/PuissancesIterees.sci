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
