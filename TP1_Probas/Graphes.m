Neumann = csvread('_von_neumann.csv');
figure('Name', 'von neumann')
hist (Neumann)

Twister =  csvread('_twister.csv');
figure('Name', 'twister')
hist (Twister)

Aes = csvread('_aes.csv');
figure('Name', 'aes')
hist(Aes)

Rang_low = csvread('_rand_low.csv');
figure('Name', 'rand low')
hist(Rang_low)

Rang_high = csvread('_rand_high.csv');
figure('Name', 'rand high')
hist(Rang_high)