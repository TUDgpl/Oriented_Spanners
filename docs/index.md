<script src="https://cdn.mathjax.org/mathjax/latest/MathJax.js?config=TeX-AMS-MML_HTMLorMML" type="text/javascript"></script>
<style>
* {
  box-sizing: border-box;
}

.column {
  float: left;
  width: 50%;
  padding: 5px;
}

/* Clearfix (clear floats) */
.row::after {
  content: "";
  clear: both;
  display: table;
}
</style>

## Overview

Given a point set P and a parameter t, an oriented t-spanner G is an oriented subgraph of the complete bi-directed graph, such that for every pair of points, the shortest cycle in G containing those points is at most a factor t longer than their shortest oriented path in the complete bi-directed graph. 

This open source project collects a set of algorithms to comput oriented spanners for 1D point sets.


## Licence
This project is under MIT licence.

## Reference
**Oriented Spanners**<be>
Kevin Buchin, Joachim Gudmundsson, Antonia Kalb, Aleksandr Popov, Carolin Rehs, André van Renssen, Sampson Wong<be>
ESA 2023: 26:1-26:16.
[[bibtex]](https://dblp.org/rec/conf/esa/BuchinGK0RRW23.bib) [[doi]](https://dl.acm.org/doi/10.4230/LIPICS.ESA.2023.26)


Please acknowledge our work if you publish your result using our algorithms or code.



## Support
Please write to us if you have questions.

We are glad to get any comments and error reports.

A random instance generator is available upon request.
