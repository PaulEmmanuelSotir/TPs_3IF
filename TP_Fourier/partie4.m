
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%% PARTIE 4 %%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
function [ ] = partie4()
h_height = 0;
h_width = 0;
%for h_height= 0:4
    %for h_width= 0:4
        correct_image('PhotoTexte.png', h_height, h_width);
        %pause(1);
    %end
%end
end

function correct_image(im_name, h_height, h_width)
    % Cr�ation et affichage de la r�ponse impulsionelle
    h = zeros(512, 512);
    for i= 1:(h_height*2+1)
        for j=1:(h_width*2+1)
            h(256-4 + i, 256-4 + j) = 1/((2*h_width+1)*(2*h_height+1));
        end
    end

    % Calcul de la FFT 2D de la r�ponse impulsionelle
    H=fftshift(fft2(ifftshift(h))); % TODO: peut �tre enlever un shift ici (h deja centr�)

    % Lecture de l'image de r�f�rence / image id�ale
    [im_ref, map]=imread('PhotoRef.png') ;

    % Calcul de la FFT 2D de l'image de r�f�rence
    IM_REF=fftshift(fft2(ifftshift(im_ref)));

    % Calcul de Pi
    Pi = zeros(512,512);
    for i= 1:512
        for j=1:512
            Pi(i,j) = abs(IM_REF(i,j)) * abs(IM_REF(i,j));
        end
    end

    % Calcul de dr
    DR = IM_REF.*H;
    dr = fftshift(ifft2(ifftshift(DR)));

    % Calcul de dq
    dq = round(dr);

    % Calcul de b et B
    b = dq - dr;
    B = fftshift(fft2(ifftshift(b)));

    % Calcul de Pb
    Pb = zeros(512,512);
    for i= 1:512
        for j=1:512
            Pb(i,j) = abs(B(i,j)) * abs(B(i,j));
        end
    end

    % TODO: verifier la presence de 0 dans H

    % Construction du filtre de Wiener
    W = zeros(512,512);
    for i= 1:512
        for j=1:512
            Ph = abs(H(i,j)) * abs(H(i,j));
            W(i,j)= 1/H(i,j) * Ph / ( Ph + Pb(i,j)/Pi(i,j) );
        end
    end

    % Lecture de l'image � traiter
    [d, map]=imread(im_name);

    % Calcul de la FFT 2D de l'image � corriger
    D = fftshift(fft2(ifftshift(d)));

    % Correction de l'image
    IM_TRAITEE = D.*W;
    im_traitee = fftshift(ifft2(ifftshift(IM_TRAITEE)));

    % Recadrage du spectre d'amplitude pour l'affichage en grayscale
    im_netb=abs(im_traitee)+1;
    maxi=max(max(im_netb));
    mini=min(min(im_netb));
    im_netb=(log(im_netb)-log(mini))/(log(maxi)-log(mini))*255;

    % Affichage de l'image corrig�e
    strcat(strcat('h_height=', num2str(2*h_height+1)), strcat(', h_width=', num2str(2*h_width+1)))
    figure(3)
    image(im_netb)
    colormap(map)

    % Create sliders to choose h_width and h_height
    global width_slider;
    global height_slider;
    width_slider = uicontrol('style','slider', 'Min', 0, 'Max', 4, 'Value', h_width, 'Position', [220 10 200 20], 'Callback', @width_changed);
	height_slider = uicontrol('style','slider', 'Min', 0, 'Max', 4, 'Value', h_height, 'Position', [620 10 200 20], 'Callback', @height_changed);

    uicontrol('Style','text',...
        'Position',[100 10 120 20],...
        'String', strcat('h_width=', num2str(2*h_width+1)));
    
    uicontrol('Style','text',...
        'Position',[500 10 120 20],...
        'String', strcat('h_height=', num2str(2*h_height+1)));
end

function width_changed(source,callbackdata)
    global height_slider;
    
    h_width = round(get(source,'Value'));
    h_height = round(get(height_slider,'Value'));
    
    correct_image('PhotoTexte.png', h_height, h_width);
end

function height_changed(source,callbackdata)
    global width_slider;
    
    h_width = round(get(width_slider,'Value'));
    h_height = round(get(source,'Value'));
    
    correct_image('PhotoTexte.png', h_height, h_width);
end
%%%%%%%%%%%%%%%%%%%%%%%%% FIN PARTIE 4 %%%%%%%%%%%%%%%%%%%%%%%%%