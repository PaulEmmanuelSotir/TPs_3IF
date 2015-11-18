
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%% PARTIE 3 %%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [ ] = partie3()
global f1;
global f2;

a = -5; b = 5; N = 32768;
f1 = 500; f2 = 750;

% Affichage du signal s1
transfo_Fourier_discrete(@s1, a, b ,N);
% Affichage du signal s2
transfo_Fourier_discrete(@s2, a, b ,N);

% Modulation
transfo_Fourier_discrete(@c, a, b ,N);

% Demodulation
% Affichage du signal s1 démodulé
transfo_Fourier_discrete(@s1_demodulee, a, b ,N);
% Affichage du signal s2 démodulé
transfo_Fourier_discrete(@s2_demodulee, a, b ,N);

end

%%%%%%%% s1(t) %%%%%%%%
function [ y ] = s1( t )
y = 0;
for n=1:5
    y = y + n * cos(2*pi*20*n*t);
end
end

%%%%%%%% s2(t) %%%%%%%%
function [ y ] = s2( t )
y = 0;
for n=1:5
    y = y + (6-n) * cos(2*pi*20*n*t);
end
end

%%%%%%%% c(t) %%%%%%%%
function [ y ] = c( t )
global f1;
global f2;
y = s1(t)*cos(2*pi*f1*t) + s2(t)*cos(2*pi*f2*t);
end

%%%%%%%% s1_demodulee(t) %%%%%%%%
function [ y ] = s1_demodulee( t )
global f1;
y = 2*c(t)*cos(2*pi*f1*t);
end

%%%%%%%% s2_demodulee(t) %%%%%%%%
function [ y ] = s2_demodulee( t )
global f2;
y = 2*c(t)*cos(2*pi*f2*t);
end

%%%%%%%%%%%%%%%%%%%%%%%%% FIN PARTIE 3 %%%%%%%%%%%%%%%%%%%%%%%%%