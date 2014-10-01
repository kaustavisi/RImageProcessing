require(fields)

imresize <- function(image, scale)
{
    imSize <- dim(image)
    imObj <- list(x=1:imSize[1], y=1:imSize[2], z=image)

    outDim <- round(imSize * scale)
    out <- matrix(NA, nrow=outDim[1], ncol=outDim[2])

    outCord <- as.matrix(expand.grid(seq_len(outDim[1]),
                                     seq_len(outDim[2])))
    
    location <- outCord
    location[,1] <- scaling(outCord[,1], c(1,outDim[1]))
    location[,2] <- scaling(outCord[,2], c(1,outDim[2]))

    out[outCord] <- interp.surface(imObj, location)
    out

}

scaling <- function(x, newRange)
{
    rangex <- range(x)
    newRange[1] + (x - rangex[1]) * diff(newRange)/diff(range(x))
}
