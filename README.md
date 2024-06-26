Oriented Spanners of 1D Point Sets

Github Page: https://tudgpl.github.io/Oriented_Spanners/
# Requirements
<ol>
<li> Glucose solver : https://github.com/audemard/glucose/</li>
<li>  g++ >15.0 </li>
 <li>  boost >.17.5 </li>
</ol>
# Description
Our Framework contains the following algorithms.
*sat1 : exact sat-model based solver to find an optimal 1-PPB using Glucose SAT solver.
*sat : exact sat-model based solver to find an optimal 2-PPB using Glucose SAT solver.
*greedy: a greedy algorithm to find an optimal 1-PPB by selecting the shortes edges.
*dp: a dynamic programming algorithm to find an optimal 1-PPB.


# Installation
Compile the source with camke </br> 
make </br>
Default Paths:</br>
├── src <br />
├── doc <br />
├── build <br />
  ├── src  # excutable files OriSpanner, glucose-simp <br />



# Usage
./oriSpanner  -f \<instance\> [options]

--help, -h : output this help</br>
--algorithm, -a : algorithm in use (see options below) </br>
--dictionary, -d : solution folder </br>
 --ipe, -i : ipe drawing input file </br>
 --short, -s : get optimal solutions with only short edge-distance edges, in combination with the flag -l </br>
 --length, -l : only using short edge distance edges (pi, pj) where j -i < l </br>
 --path, -p : SAT solver bin path </br>
 --tmp, -t : temp folder to store temperary DIMAS files generated by SAT solvers </br>
 *More details see the paper \"Oriented Spanners\" <https://arxiv.org/abs/2306.17097> </br>

# Generator
how to use: <be>
run the oSpannerIG.py <br>
you may need to change the values of the following variables:<br>
nt_data_path: path for the generated instance<br>
W: width of the range<br>
H: Height of the range (not used for 1D point sets)<br>
instance_number_random: number of instances to generate<br>





