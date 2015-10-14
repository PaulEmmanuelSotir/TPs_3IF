width = 30;
height = 15;
cut_pos = 12;
DotNum = width*height;
% Laplacien(u) = d²u/dx² + d²u/dy² = du/dt(x,y)
% du/dt(x,y) = u(x,y,t) - u(x,y,t-1) = u(x-1,y,t) + u(x+1,y,t) + u(x,y-1,t) + u(x,y+1,t) - 4*u(x,y,t)
% Soit u(x,y,t) = u(x-1,y,t) + u(x+1,y,t) + u(x,y-1,t) + u(x,y+1,t) - 4*u(x,y,t) + u(x,y,t-1) avec u(x,y,0) = f(x,y) connu

% Create vector representation of initial temperature map, X0
X_prev = zeros(DotNum);
X_prev(7*width + 17) = 100; 					% 300°C dot I
X_prev(7*width + 18) = 100; 					% 300°C dot J
X_prev(7*width + 19) = 100; 					% 300°C dot K

while(1)
	% Create linear system matrix, A
	A = zeros(DotNum, DotNum);
	for n=0:DotNum
		if n <= width || n > (width-1)*height
			if mod(n, cut_pos) ~=  0 % 3+2 neib dot
				
			else % 3 neib dot
				
			end
		else if mod(n, cut_pos) ~=  0
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
	end

	% Resolve AX=X_prev linear system to get next temperature state, X
	X = rand(DotNum);
	[X, m, error] = Relax( A, X_prev, X, 1.2);

	% Display resulting heat map, X
	Figure(1)
	[HeatMap, padded] = vec2mat(X, width);
	surf(HeatMap)
	
	X_prev = X;
end
end