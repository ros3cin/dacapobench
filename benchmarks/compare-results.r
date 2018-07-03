library("effsize")
args = commandArgs(trailingOnly=TRUE)
if(length(args) < 4) {
    stop("Please, inform two results file path, the number of initial samples to disconsider and the total amount of samples")
}
samplesToDisconsider = as.numeric(args[3])
samplesTotal = as.numeric(args[4])
sample1 <- read.csv(args[1],header=FALSE,sep=",",dec=".", quote="")
sample2 <- read.csv(args[2],header=FALSE,sep=",",dec=".", quote="")

sample1 <- sample1[1,]
sample1 <- as.numeric(unlist(sample1))
sample1 <- sample1[samplesToDisconsider:samplesTotal]

sample2 <- sample2[1,]
sample2 <- as.numeric(unlist(sample2))
sample2 <- sample2[samplesToDisconsider:samplesTotal]

wilcox.test(sample1,sample2)

mean1 <- mean(sample1)
mean1
sd(sample1)

mean2 <- mean(sample2)
mean2
sd(sample2)

cliff.delta(sample1, sample2)

sprintf("The improvement is %f",1-(min(mean1,mean2)/max(mean1,mean2)));
