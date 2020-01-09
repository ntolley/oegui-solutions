data_buf(1:end-nSamples,:) = data_buf(1+nSamples:end,:);
data_buf(end-nSamples+1:end,:) = X(:,1:96);

avg_buf = movmean(data_buf, smooth_win, 1);

output = avg_buf(:,1:96) * decode_param(1:96);
X(:,1) = output(end-(50+nSamples):end-(51)) .*100;

% if plot_count == plot_freq
% 	subplot(2,s1,1)
% 	plot(data_buf(plot_win:end-plot_win,chan_sel),'b','LineWidth',2)
% 	title(['Channel ', num2str(chan_sel), ' Firing Rate'])
% 	xlim([0 1200])
% 	ylim([-25 250])
% 	xlabel('Samples')
% 
% 
% 	subplot(2,1,2)
% 	plot(output(plot_win:end-plot_win),'r','LineWidth',2);
% 	title('Decode Output')
% 	xlim([0 1200])
% 	ylim([0.4 0.8])
% 	xlabel('Samples')
% 
% 	plot_count = 0;
% end

% plot_count = plot_count + 1;