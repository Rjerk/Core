nsamples = 5;
npoints = 50;

for k = 1 : nsamples
    iteration_string = ['iteration # ', int2str(k)];
    disp(iteration_string);
    current_data = rand(npoints, 1);
    sample_mean(k) = mean(current_data)
end

overall_mean = mean(sample_mean)

if overall_mean < .48
    disp('Mean is less than expected.')
elif overall_mean > .51
    disp('Mean is greater than expected.')
else
    disp('Mean is within the expected range')
end
