setwd("C:/Users/46013/Desktop")

hotdogs <- read.csv(
    "http://faculty.cs.tamu.edu/tlw/Courses/fall11/csce110/code/hotdog-contest/nathans-hotdog-data.csv",
    sep = ",",
    header = TRUE)

# Default barchart
barplot(hotdogs$Hot.dogs.eaten)

fill_colors <- c()
for ( i in 1:length(hotdogs$Country) ) {
    if (hotdogs$Country[i] == "United States") {
        fill_colors <- c(fill_colors, "#821122")
    } else {
        fill_colors <- c(fill_colors, "#cccccc")
    }
}

barplot(hotdogs$Hot.dogs.eaten, names.arg=hotdogs$Year,
        col=fill_colors, border=NA, xlab="Year", ylab="HDB eaten")
