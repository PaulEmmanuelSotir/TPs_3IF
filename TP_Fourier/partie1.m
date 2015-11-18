
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%% PARTIE 1 %%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [ ] = partie1()
global a; global b; global N;
global Freq0; global Beta; global Cst; global Tau; global deltaT;

a = -5; b = 5; N = 32768;

%DeltaF = Fe / N;
disp('Te = ')
Te = (b-a) / N
disp('Fe = ')
Fe = 1 / Te

% on choisit un 'Freq0' tel qu'il y ait un nombre entier de periodes sur [a,b]
Freq0 = 100; Beta = 1000; Cst = 7; Tau = 0.5;
% on choisit un 'DeltaT' tel que l'échantillonage de x4(t) conserve le dirac
%deltaT = 10 * (b - a) / N; TODO: enlever ça si ok
deltaT = 2 * Te;

transfo_Fourier_discrete(@x0, a, b ,N);
transfo_Fourier_discrete(@x1, a, b ,N);
transfo_Fourier_discrete(@x2, a, b ,N);
transfo_Fourier_discrete(@x3, a, b ,N);
transfo_Fourier_discrete(@x4, a, b ,N);
transfo_Fourier_discrete(@x5, a, b ,N);
transfo_Fourier_discrete(@x6, a, b ,N);
transfo_Fourier_discrete(@x6_periodic, a, b ,N);
transfo_Fourier_discrete(@x7, a, b ,N);

end

%%% Constantes globales %%%
% (enlever si inutile)
%global a; global b; global N;
%global Freq0; global Beta; global Cst; global Tau;

%%%%%%%%%% X0(t) %%%%%%%%%%
function [ y ] = x0( t )
global Cst;
y = Cst;
end

%%%%%%%%%% X1(t) %%%%%%%%%%
function [ y ] = x1(t)
global Freq0;
y = cos(2 * pi * t * Freq0);
end

%%%%%%%%%% X2(t) %%%%%%%%%%
function [ y ] = x2( t )
global Freq0;
y = sin(2 * pi * t * Freq0);
end

%%%%%%%%%% X3(t) %%%%%%%%%%
function [ y ] = x3( t )
global Beta;
if(t > 0)
    y = exp(-Beta*t);
else
    y = 0;
end
end

%%%%%%%%%% X4(t) %%%%%%%%%%
function [ y ] = x4( t )
global deltaT;
if t == deltaT
    y = 1;
else
    y = 0;
end
end

%%%%%%%%%% X5(t) %%%%%%%%%%
function [ y ] = x5( t )
global Freq0;
y = exp(1i * 2 * pi * Freq0 * t);
end

%%%%%%%%%% X6(t) %%%%%%%%%%
function [ y ] = x6( t )
global Tau;
offset = 2;
if t < -Tau / 2 + offset || t > Tau / 2 + offset
    y = 0;
else
    y = 1;
end
end

%%%%%% x6_periodic(t) %%%%%
function [ y ] = x6_periodic( t )
global Tau;
tmod2tau = abs(mod(2*t/Tau,2));
if (0 <= tmod2tau && tmod2tau < 1)
    y = 1;
else 
    y = 0;
end
end

%%%%%%%%%% x7(t) %%%%%%%%%%
function [ y ] = x7( t )
y = exp(-pi * t * t);
end

%%%%%%%%%%%%%%%%%%%%%%%%% FIN PARTIE 1 %%%%%%%%%%%%%%%%%%%%%%%%%