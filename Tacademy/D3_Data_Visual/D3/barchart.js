var svgHeight = 235;
var barElements;
var dataSet = [120, 70, 175, 80, 220];

barElements = d3.select("#myGraph")
    .selectAll("rect")
    .data(dataSet);

barElements.enter()
    .append("rect")
    .attr("class", "bar")
    .attr("height", function(d){
        return d;
    })
    .attr("weight", "20")
    .attr("x", function(d, i){
        console.log(i);
        return i * 30;
    })
    .attr("y", function(d) {
        return svgHeight - d;
    });

textElements = d3.select("#myGraph")
    .select("#barNum")
    .data(dataSet)    .attr("x", function(d, i){
        console.log(i);
        return i * 30;
    })
    .attr("y", function(d) {
        return svgHeight - d;
    });