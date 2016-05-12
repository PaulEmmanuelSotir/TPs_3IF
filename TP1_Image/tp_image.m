%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%% tp_image %%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function tp_image

[im, map] = imread('paysage.jpeg');
size(im)
size(map)

mapndg = ([0:255]'/255)*[1 1 1];
imndg = 0.2126 * im(:,:, 1) + 0.7152 * im(:,:, 2) + 0.0722 * im(:,:, 3);

figure(1)
image(imndg)
colormap(mapndg)

figure(2)
image(im)

[NL, NC] = size(imndg)

% Histogramme
histo = zeros(1,256);
for i=1:NL
    for j=1:NC
       histo(imndg(i, j) + 1) = histo(imndg(i, j) + 1) + 1;
    end
end

figure(3)
plot(histo)

% Histogramme cumulé
histo_cum = zeros(1,256);
histo_cum(1) = histo(1);
for i=2:256
    histo_cum(i) = histo_cum(i-1) + histo(i);
end

figure(4)
plot(histo_cum)

% Seullage
seuil = 100;
imSeuil = zeros(NL, NC);
for i=1:NL
    for j=1:NC
		if(seuil < imndg(i,j))
			imSeuil(i,j) = 255;
		end
    end
end

figure(5)
image(imSeuil)
colormap(mapndg)

imRec = zeros(NL, NC);
imndg = double(imndg);
mini = min(min(imndg));
maxi = max(max(imndg))
imRec = floor(255* ((imndg - mini)/(maxi - mini)));

figure(6)
image(imRec)
colormap(mapndg)

% Histogramme
histoRec = zeros(1,256);
for i=1:NL
    for j=1:NC
       histoRec(imRec(i, j) + 1) = histoRec(imRec(i, j) + 1) + 1;
    end
end

figure(7)
plot(histoRec)

%contraste
K = 2;
moy = mean(mean(imndg));
imcont = K*(imndg-moy) + moy;

figure(8)
image(imcont)
colormap(mapndg)

%convolution
masque = [0 1 0;1 -4 1;0 1 0];
K = 1;
offset = 128;

imconv = zeros(NL,NC);
for i=2:NL-1
    for j=2:NC-1
       imconv(i,j) = offset + sum(sum(imndg(i - 1:i + 1, j - 1:j + 1).* masque)) / K;
    end
end

figure(9)
image(imconv)
colormap(mapndg)

end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%