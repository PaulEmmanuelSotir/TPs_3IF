
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%% PARTIE 2 %%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [ ] = partie2()
global f;

a = -5; b = 5; N = 32768;

fmid = 3 * N / (b-a) - 40;
fmid
f = fmid;
%for ff=1:100
 %   f = fmid - 20 + 2*ff;
    transfo_Fourier_discrete(@g, a, b ,N);
%end

end

%%%%%%%%%% g(t) %%%%%%%%%%
function [ y ] = g( t )
global f;
deltaf = 40;
y = sin(2*pi*f*t) + 2*sin(2*pi*(f + deltaf)*t) + 3*sin(2*pi*(f + 2*deltaf)*t);
end

%%%%%%%%%%%%%%%%%%%%%%%%% FIN PARTIE 2 %%%%%%%%%%%%%%%%%%%%%%%%%