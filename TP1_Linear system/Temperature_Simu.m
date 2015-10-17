width = 30;
height = 15;
cut_pos = 12;
DotNum = width*height;
T = 457;

%Avg_max = repmat(3*300/DotNum+0.1, DotNum,1);
%Avg_min = repmat(3*300/DotNum-0.1, DotNum,1);

% Create vector representation of temperature map, X_previous
X_previous = zeros(DotNum, 1);
X_previous(7*width + 16) = 300; 					% 300°C dot I
X_previous(7*width + 17) = 300; 					% 300°C dot J
X_previous(7*width + 18) = 300; 					% 300°C dot K

for t=1:T
    % Create linear system matrix, A
    A = zeros(DotNum, DotNum);
    for n=1:DotNum
        if mod(n, width) ~=  cut_pos && n > width && n <= (height-1)*width
            if mod(n, width) ==  0
                % 4-neighbors-point
                A(n, n) = -4;
                A(n, n-1) = 1;
                A(n, n-width+cut_pos-1) = 1;
                A(n, n+width) = 1;
                A(n, n-width) = 1;
            else if mod(n, width) == 1
                    % 4-neighbors-point
                    A(n, n) = -4;
                    A(n, n+cut_pos-1) = 1;
                    A(n, n+1) = 1;
                    A(n, n+width) = 1;
                    A(n, n-width) = 1;
                else
                    % 4-neighbors-point (Bn = 0 = -4Xn + Xn+1 + Xn-1 + Xn+width + Xn-width)
                    A(n, n) = -4;
                    A(n, n+1) = 1;
                    A(n, n-1) = 1;
                    A(n, n+width) = 1;
                    A(n, n-width) = 1;
                    
                end
            end
        else if mod(n, width) ==  cut_pos
                if n == cut_pos
                    % 5-neighbors-point (Bn = 0 = -4Xn + Xn+1 + Xn-1 + Xn+width + Xn-width)
                    A(n, n) = -5;
                    A(n, n+1) = 1;
                    A(n, n-1) = 1;
                    A(n, n+width) = 1;
                    A(n, 1) = 1;
                    A(n, width) = 1;
                    else if n == cut_pos + DotNum - width
                    	% 5-neighbors-point (Bn = 0 = -4Xn + Xn+1 + Xn-1 + Xn+width + Xn-width)
                        A(n, n) = -5;
                        A(n, n+1) = 1;
                        A(n, n-1) = 1;
                        A(n, n-width) = 1;
                        A(n, DotNum-width+1) = 1;
                        A(n, DotNum) = 1;
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
            else if n == 1
                    % 3-neighbors-point
                    A(n, n) = -3;
                    A(n, n+1) = 1;
                    A(n, n+width-1) = 1;
                    A(n, n+width) = 1;
                    else if n == width
                             % 3-neighbors-point
                            A(n, n) = -3;
                            A(n, n-width+1) = 1;
                            A(n, n-1) = 1;
                            A(n, n+width) = 1;
                            else if n == DotNum - width +1
                                     % 3-neighbors-point
                                    A(n, n) = -3;
                                    A(n, n+1) = 1;
                                    A(n, n+width-1) = 1;
                                    A(n, n-width) = 1;
                                    else if n == DotNum
                                            % 3-neighbors-point
                                            A(n, n) = -3;
                                            A(n, n-width+1) = 1;
                                            A(n, n-1) = 1;
                                            A(n, n-width) = 1;
                                            else if n < width
                                                % 3-neighbors-point
                                                A(n, n) = -3;
                                                A(n, n+1) = 1;
                                                A(n, n-1) = 1;
                                                A(n, n+width) = 1;
                                            else if n > DotNum-width
                                                % 3-neighbors-point bis
                                                A(n, n) = -3;
                                                A(n, n+1) = 1;
                                                A(n, n-1) = 1;
                                                A(n, n-width) = 1;
                                                end
                                                end
                                        end
                                end
                        end
                end
            end
        end
    end
    
    X = expm(A)*X_previous;
  
    % Display resulting heat map, X
    figure(1)
    HeatMap = reshape(X, width, height);
    surf(HeatMap)
    
    %if X < Avg_max && Avg_min < X
   %     break;
   % end
    
    X_previous = X;
end