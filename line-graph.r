#!/usr/bin/Rscript

data=read.csv('file.csv')   

dates <- as.POSIXct(data[, c(2)], origin="1970-01-01")

pdf(file="myplot.pdf")

plot(
    dates,
    data$x,
    cex = 0.9,
    type = "l",
    xaxt = "n"
)

axis(1, dates, format(dates, "%d-%m-%Y %H-%i-%s"))

dev.off()