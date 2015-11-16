function [vf]=tfourinv(vFw)


%tfi	Transform�e de Fourier Inverse discr�te.
% 	tfi(vFw) est la transform�e de Fourier inverse discr�te de 
%	la fonction F(w) dont (ne) echantillons sont rang�s dans le 
%	vecteur ligne vFw. La valeur F(0) doit �tre dans 
%	l'echantillon (ne/2 + 1).
%
%  	Voir aussi tf, IFFT, FFT2, IFFT2, FFTSHIFT.



if (size(vFw,1)==1)

	ne=size(vFw,2);

	i=sqrt(-1);
	nes2=ne/2;
	for n=1:ne,
	   	vFw(n)=exp(-i*(n-nes2+1)*pi)*vFw(n);
	end
	vFw=fftshift(vFw);
	vf=ifft(vFw);
else 	'tfi : Le vecteur des donn�es doit �tre un vecteur ligne'
end