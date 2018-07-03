args = commandArgs(trailingOnly=TRUE)
if(length(args) < 3) {
    stop("Please, inform the results file path, the number of initial samples to disconsider and the total amount of samples")
}
samplesToDisconsider = as.numeric(args[2])
samplesTotal = as.numeric(args[3])
results <- read.csv(args[1],header=FALSE,sep=",",dec=".", quote="")
results <- results[1,]
results <- as.numeric(unlist(results))
results <- results[samplesToDisconsider:samplesTotal]
mean(results)
sd(results)
