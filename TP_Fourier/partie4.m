
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%% PARTIE 4 %%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% fft2 puis fftshift pour avoir une representation centrée en 0
function [ ] = partie4()
a= 9;
b= 9;
%for a= 1:9
%    for b= 1:9
        % Création et affichage de la réponse impulsionelle
        h = zeros(512, 512);
        for i= 1:a
            for j=1:b
                h(256-4 + i, 256-4 + j) = 1/(b*a);
            end
        end
        figure(1)
        image(h)

        % Calcul de la FFT 2D de la réponse impulsionelle
        H=fftshift(fft2(h));

        % Lecture de l'image de référence / image idéale
        [im_ref, map]=imread('PhotoRef.png') ;

        % Calcul de la FFT 2D de l'image de référence
        IM_REF=fftshift(fft2(im_ref));

        Pi=IM_REF.*IM_REF;

        % Calcul de Pi
        Pi = zeros(512,512);
        for i= 1:512
            for j=1:512
                Pi(i,j)=abs(IM_REF(i,j))*abs(IM_REF(i,j));
            end
        end

        % Calcul de dr
        DR = IM_REF.*H;
        dr = ifft2(ifftshift(DR));
        
        % Calcul de Pb
        dq = zeros(512,512);
        for i= 1:512
            for j=1:512
                dq(i,j)=round(dr(i,j));
            end
        end
        
        % Calcul de b et B
        b = dq - dr;
        B = fftshift(fft2(b));

        % Calcul de Pb
        Pb = zeros(512,512);
        for i= 1:512
            for j=1:512
                Pb(i,j)=abs(B(i,j)) * abs(B(i,j));
            end
        end

        % Construction du filtre de Wiener
        W = zeros(512,512);
        for i= 1:512
            for j=1:512
                Ph = abs(H(i,j)) * abs(H(i,j));
                W(i,j)=1/H(i,j) * Ph / ( Ph + Pb(i,j)/Pi(i,j) );
            end
        end

        % Lecture de l'image à traiter
        [d, map]=imread('PhotoTexte.png') ;
        figure
        image(d)
        colormap(map)

        % Calcul de la FFT 2D de l'image à corriger
        D = fftshift(fft2(d));

        size(D)
        size(W)
        IM_TRAITEE = D.*W;
        im_traitee = ifft2(ifftshift(IM_TRAITEE));

        im_netb=abs(im_traitee)+1;
        maxi=max(max(im_netb));
        mini=min(min(im_netb));
        im_netb=(log(im_netb)-log(mini))/(log(maxi)-log(mini))*255;
        figure
        image(im_netb)
        colormap(map)
%    end
%end
end

%%%%%%%%%%%%%%%%%%%%%%%%% FIN PARTIE 4 %%%%%%%%%%%%%%%%%%%%%%%%%