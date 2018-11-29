install.packages("ggplot2")
library("ggplot2")

setwd("~/mownit/seria4/")

result = read.csv("result.csv")
avg_result = aggregate( Time ~ Size:Algorithm, data=result, FUN=mean)
avg_result$sd = aggregate( Time ~ Size:Algorithm, data=result, FUN=sd)

data = data.frame(Algorithm = avg_result$Algorithm, Size = avg_result$Size, Time = avg_result$Time, sd = avg_result$sd$Time)

dataNaive <- subset(data, Algorithm == "1")
dataNaive$Algorithm = "1"
dataBetter <- subset(data, Algorithm == "2")
dataBetter$Algorithm = "2"
dataBLAS <- subset(data, Algorithm == "3")
dataBLAS$Algorithm = "3"

data1 = lm(Time ~ poly(Size, 1, raw=TRUE), data=dataNaive)
data2 = lm(Time ~ poly(Size, 2, raw=TRUE), data=dataBetter)
data3 = lm(Time ~ poly(Size, 3, raw=TRUE), data=dataBLAS)

data2Naive = data.frame(Size = seq(90,1100, length.out=500))
data2Naive$Algorithm = "1"
data2Naive$fit = predict(data1, data2Naive)

data2Better = data.frame(Size = seq(90,1100, length.out=500))
data2Better$Algorithm = "2"
data2Better$fit = predict(data2, data2Better)

data2BLAS = data.frame(Size = seq(90,1100, length.out=500))
data2BLAS$Algorithm = "3"
data2BLAS$fit = predict(data3, data2BLAS)

ggplot(data,aes(x=Size, y=Time, group=Algorithm)) + geom_errorbar(aes(ymin = Time - sd, ymax = Time + sd), width=40) + 
  geom_point() + 
  geom_line(data=data2BLAS, aes(Size,fit)) + geom_line(data=data2Better, aes(Size,fit)) + geom_line(data=data2Naive, aes(Size,fit))
