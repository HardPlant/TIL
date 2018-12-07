var svgHeight = 235;
var barElements;
var dataSet = [120, 70, 175, 80, 220];

barElements = d3.select("#myGraph")
    .selectAll("rect")
    .data(dataSet);

barElements.enter()
    .append("rect")
    .attr("height", "20")
    .attr("weight", "20")
    .attr("x", "1")
    .attr("y", "1")
textElements = d3.select("#myGraph")
    .select("#barNum")
    .data(dataSet);