function [ vec, lambda ] = PuissancesIterees( A, k_max )
n = size(A, 1);
Y = rand(n,1);

for k=0:k_max
    X = Y/norm(Y);
    Y = A*X;
end

vec = Y/norm(Y);
lambda = norm(Y);
if sign(lambda * Y) ~= sign(A*Y)
    lambda = lambda* (-1);

end
