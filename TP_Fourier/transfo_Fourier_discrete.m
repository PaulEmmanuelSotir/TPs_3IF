
%%%%%%%%%% transformee de fourier discrete %%%%%%%%%%
function [ ] = transfo_Fourier_discrete( Xa, a, b, N)

Te = (b - a) / N;
Fe = 1 / Te
Xn_t = zeros(1, N);
freqXaxis = zeros(1, N);
timeXaxis = zeros(1, N);

% Echantillonage de la fonction Xa
for n=1:N
    Xn_t(1, n) = Xa((n-1)*Te + a);
    timeXaxis(1,n) = (n-1) * Te + a;
    freqXaxis(1,n) = (n-1) * Fe/N - Fe/2;
end

% Transformée de fourier de la fonction échantillonée
Xn_f = tfour(Xn_t);

% Calcul de la représentation module/phase de la transformée
% TODO: voir si on peut l'appliquer simplement aux vecteur (sans boucle)
phase_f = zeros(1, N);
mod_f = zeros(1, N);
for n=1:N
    phase_f(1,n) = angle(Xn_f(1,n));
    mod_f(1,n) = abs(Xn_f(1,n));
end

% Affichage de la transformée de fourier (phase/module et reel/imag.)
%hold on
figure;

% Affichage du signal d'origine
subplot(2,3,1)
plot(timeXaxis ,Xn_t)
xlim([a,b])
title('Original function')

% Affichage du signal reconstruit (fourier inverse)
signalReconstruit = tfourinv(Xn_f);
subplot(2,3,4)
plot(timeXaxis, signalReconstruit)
xlim([a,b])
title('Fonction reconstruite')

% Affichage de la partie réelle de la transformée de fourier
subplot(2,3,2)
plot(freqXaxis, real(Xn_f))
xlim([-Fe/2,Fe/2])
title('FT Real part')

% Affichage de la partie imaginaire de la transformée de fourier
subplot(2,3,5)
plot(freqXaxis, imag(Xn_f))
xlim([-Fe/2,Fe/2])
title('FT Imag. part')

% Affichage de la phase de la transformée de fourier
subplot(2,3,3)
plot(freqXaxis, phase_f)
xlim([-Fe/2,Fe/2])
title('FT Phase')

% Affichage du module de la transformée de fourier
subplot(2,3,6)
plot(freqXaxis, mod_f)
xlim([-Fe/2,Fe/2])
title('FT Module')

% TODO: error = Xn_t - signalReconstruit
end
