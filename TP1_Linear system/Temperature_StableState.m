width = 30;
height = 15;
cut_pos = 12;
DotNum = width*height;

% Create vector representation of temperature map, B
B = zeros(DotNum);
B(1:width) = 50;						% 50°C top border
B(((height-1)*width+1):DotNum) = 50;	% 50°C bottom border
for h=3:11
	B((h*width+22):(h*width+23)) = 10;	% 10°C rectangle
end
B(7*width + 17) = 100; 					% 100°C dot 1
B(7*width + 18) = 100; 					% 100°C dot 2
B(7*width + 19) = 100; 					% 100°C dot 3

% Create linear system matrix, A
A = zeros(DotNum, DotNum);
for n=0:DotNum
	if B(n) == 0
		if mod(n, cut_pos) ~=  0
			% 4-neighbors-point (Bn = 0 = -6Xn + Xn+1 + Xn-1 + Xn+width + Xn-width)
			A(n, n) = -4;
			A(n, n+1) = 1;
			A(n, n-1) = 1;
			A(n, n+width) = 1;
			A(n, n-width) = 1;
		else
			% 6-neighbors-point (Bn = 0 = -6Xn + Xn+1 + Xn-1 + Xn+width + Xn-width + Xn-cut_pos+1 + Xn-cut_pos+width)
			A(n, n) = -6;
			A(n, n+1) = 1;
			A(n, n-1) = 1;
			A(n, n+width) = 1;
			A(n, n-width) = 1;
			A(n, n-cut_pos+1) = 1;		% left border neighbor
			A(n, n-cut_pos+width) = 1;	% right border neighbor
		end
	else
		A(n, n) = 1; % Constant temperature (Bn = Const = Xn)
	end
end

% Resolve AX=B linear system to get stable temperature state, X
X = rand(DotNum);
[X, m, error] = Relax( A, B, X, 1.2);

% Display resulting heat map, X
Figure(1)
[HeatMap, padded] = vec2mat(X, width);
surf(HeatMap)

end