load('D:\Borton Lab\Blackrock\open_ephys_decoding\decode_param.mat')

chan_sel = 12;
plot_freq = 4; %How many loop cycles until a new line is plotted
smooth_win = 100; %How many samples to smooth over
plot_win = floor(smooth_win);

figure('Position', [100 100 1200 600])

data_buf = zeros(1000,96);
plot_count = 0;