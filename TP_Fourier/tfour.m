function [Fw]=tfour(vf)


%tf	Transform�e de Fourier discr�te.
% 	tf(vf) est la transform�e de Fourier discr�te de la fonction f
%       dont (ne) �chantillons sont rang�s dans le vecteur ligne vf. 
%	Ces �chantillons correspondent � des "instants" centr�s sur la 
%	valeur z�ro. La valeur de f(0) doit �tre contenue dans 
%	l'�chantillon (ne/2 + 1).
%
%  	Voir aussi tfi, IFFT, FFT2, IFFT2, FFTSHIFT.

if (size(vf,1)==1)

	ne=size(vf,2);

	i=sqrt(-1);
	nes2=ne/2;
	Fw=fft(vf);
	Fw=fftshift(Fw);
%	for n=1:ne,
%   		Fw(n)=exp(i*(n-nes2+1)*pi)*Fw(n);
%	end
        temp=[1:ne];
        Fw=(exp(i*temp*pi)*exp(-i*(nes2-1)*pi)).*Fw;

else 	'tf : Le vecteur des donn�es doit �tre un vecteur ligne'
end