<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="file">
    <name>func.h</name>
    <path>/media/Facultad/Inteligencia Computacional/TPS/ic/tp1/ejercicio1/</path>
    <filename>func_8h</filename>
    <member kind="function">
      <type>vector&lt; double &gt;</type>
      <name>init_weight</name>
      <anchorfile>func_8h.html</anchorfile>
      <anchor>a5fb26d4fcff103e0b83a9fc3e636dafb</anchor>
      <arglist>(int nd)</arglist>
    </member>
    <member kind="function">
      <type>vector&lt; double &gt;</type>
      <name>sum</name>
      <anchorfile>func_8h.html</anchorfile>
      <anchor>a43dec5e53193b67cee867a41b13b41ed</anchor>
      <arglist>(vector&lt; double &gt; y, vector&lt; double &gt; x)</arglist>
    </member>
    <member kind="function">
      <type>vector&lt; double &gt;</type>
      <name>dif</name>
      <anchorfile>func_8h.html</anchorfile>
      <anchor>ad459afc47c60132b1920c134b828dd4d</anchor>
      <arglist>(vector&lt; double &gt; y, vector&lt; double &gt; x)</arglist>
    </member>
    <member kind="function">
      <type>vector&lt; double &gt;</type>
      <name>prod_escalar</name>
      <anchorfile>func_8h.html</anchorfile>
      <anchor>a30af966d00230d254dd0e831650617ee</anchor>
      <arglist>(vector&lt; double &gt; x, double nu)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>dot</name>
      <anchorfile>func_8h.html</anchorfile>
      <anchor>aea73986969212652eff865f5b0f781e5</anchor>
      <arglist>(vector&lt; double &gt; &amp;x, vector&lt; double &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>vector&lt; double &gt;</type>
      <name>recalcular_pesos</name>
      <anchorfile>func_8h.html</anchorfile>
      <anchor>a4be1c17c506100a53f2e52c190774853</anchor>
      <arglist>(vector&lt; double &gt; pv, double tasa, double s, double se, vector&lt; double &gt; datos)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>calc_error</name>
      <anchorfile>func_8h.html</anchorfile>
      <anchor>ad68ed751f5f6ffebb8354c05dc1bd2c5</anchor>
      <arglist>(vector&lt; double &gt; &amp;x, vector&lt; double &gt; &amp;y)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>signo</name>
      <anchorfile>func_8h.html</anchorfile>
      <anchor>aaccd35f0180617d9435aed7563934dab</anchor>
      <arglist>(double valor, double a=1.0)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>sigmoide</name>
      <anchorfile>func_8h.html</anchorfile>
      <anchor>a1d5bf741433c344e3c0b25c284de6fb1</anchor>
      <arglist>(double valor, double a=1.0)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>GNUplot.h</name>
    <path>/media/Facultad/Inteligencia Computacional/TPS/ic/tp1/ejercicio1/</path>
    <filename>GNUplot_8h</filename>
    <class kind="class">GNUplot</class>
  </compound>
  <compound kind="file">
    <name>main.cpp</name>
    <path>/media/Facultad/Inteligencia Computacional/TPS/ic/tp1/ejercicio1/</path>
    <filename>main_8cpp</filename>
    <includes id="Perceptron_8h" name="Perceptron.h" local="yes" imported="no">Perceptron.h</includes>
    <member kind="function">
      <type>int</type>
      <name>sign</name>
      <anchorfile>main_8cpp.html</anchorfile>
      <anchor>a83da59ede262c2e8631f9180a4feba8a</anchor>
      <arglist>(int x)</arglist>
    </member>
    <member kind="function">
      <type>vector&lt; vector&lt; double &gt; &gt;</type>
      <name>generar_datprueba</name>
      <anchorfile>main_8cpp.html</anchorfile>
      <anchor>a6759270d95c5e1ab8994d53703ba563e</anchor>
      <arglist>(double porc, int l)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>main</name>
      <anchorfile>main_8cpp.html</anchorfile>
      <anchor>a0ddf1224851353fc92bfbff6f499fa97</anchor>
      <arglist>(int argc, char *argv[])</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Perceptron.cpp</name>
    <path>/media/Facultad/Inteligencia Computacional/TPS/ic/tp1/ejercicio1/</path>
    <filename>Perceptron_8cpp</filename>
    <includes id="Perceptron_8h" name="Perceptron.h" local="yes" imported="no">Perceptron.h</includes>
    <includes id="utils_8h" name="utils.h" local="yes" imported="no">utils.h</includes>
    <includes id="func_8h" name="func.h" local="yes" imported="no">func.h</includes>
    <member kind="function">
      <type>void</type>
      <name>particionar</name>
      <anchorfile>Perceptron_8cpp.html</anchorfile>
      <anchor>aa533be52b391d646f0ef4eb8efbc5142</anchor>
      <arglist>(int cant, float porc)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>Perceptron.h</name>
    <path>/media/Facultad/Inteligencia Computacional/TPS/ic/tp1/ejercicio1/</path>
    <filename>Perceptron_8h</filename>
    <includes id="GNUplot_8h" name="GNUplot.h" local="yes" imported="no">GNUplot.h</includes>
    <class kind="class">Perceptron</class>
  </compound>
  <compound kind="file">
    <name>utils.h</name>
    <path>/media/Facultad/Inteligencia Computacional/TPS/ic/tp1/ejercicio1/</path>
    <filename>utils_8h</filename>
    <includes id="GNUplot_8h" name="GNUplot.h" local="yes" imported="no">GNUplot.h</includes>
    <member kind="function">
      <type>vector&lt; vector&lt; double &gt; &gt;</type>
      <name>leer_csv</name>
      <anchorfile>utils_8h.html</anchorfile>
      <anchor>a2d399755384cd96d7cab7c5ac2c6cd66</anchor>
      <arglist>(const char *archivo, vector&lt; double &gt; &amp;sd)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>crear_csv</name>
      <anchorfile>utils_8h.html</anchorfile>
      <anchor>a5a39c23989a33756950aae6a1bab3926</anchor>
      <arglist>(vector&lt; vector&lt; double &gt; &gt; &amp;v, const char *name)</arglist>
    </member>
    <member kind="function">
      <type>int</type>
      <name>generar_resultados</name>
      <anchorfile>utils_8h.html</anchorfile>
      <anchor>a6e0d231e5b4cf1fc6fd3626e27ad14c2</anchor>
      <arglist>(vector&lt; vector&lt; double &gt; &gt; &amp;entradas, vector&lt; double &gt; &amp;salidas, const char *name)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>GNUplot</name>
    <filename>classGNUplot.html</filename>
    <member kind="function">
      <type></type>
      <name>GNUplot</name>
      <anchorfile>classGNUplot.html</anchorfile>
      <anchor>a45a4ddf31275b4a30d0ae9e3562c2be6</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~GNUplot</name>
      <anchorfile>classGNUplot.html</anchorfile>
      <anchor>ab25599692559395498d375449e3931c9</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator()</name>
      <anchorfile>classGNUplot.html</anchorfile>
      <anchor>aed3fab748592b3ebb9e18c92e699dfdd</anchor>
      <arglist>(const std::string &amp;command)</arglist>
    </member>
    <member kind="variable" protection="protected">
      <type>FILE *</type>
      <name>gnuplotpipe</name>
      <anchorfile>classGNUplot.html</anchorfile>
      <anchor>a5f5b0287939e9f8a91f2ff7ce6951936</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>Perceptron</name>
    <filename>classPerceptron.html</filename>
    <member kind="function">
      <type></type>
      <name>Perceptron</name>
      <anchorfile>classPerceptron.html</anchorfile>
      <anchor>a1ccbe33e4e26ee0258e63ab01507498d</anchor>
      <arglist>(double)</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>Perceptron</name>
      <anchorfile>classPerceptron.html</anchorfile>
      <anchor>a5b8f94d3ec951f153774575e2acdf582</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type></type>
      <name>~Perceptron</name>
      <anchorfile>classPerceptron.html</anchorfile>
      <anchor>a0267e40e981df9907129d858911840e7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>def_epocas</name>
      <anchorfile>classPerceptron.html</anchorfile>
      <anchor>a7f0bdf85257e3e6905d6108af60d0662</anchor>
      <arglist>(int g)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>entrenar</name>
      <anchorfile>classPerceptron.html</anchorfile>
      <anchor>a0cb4c03b50017acd1b730a3434ab83f5</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>probar</name>
      <anchorfile>classPerceptron.html</anchorfile>
      <anchor>abf06a0a2a47f075419d9943d099143ef</anchor>
      <arglist>(const char *name)</arglist>
    </member>
    <member kind="function">
      <type>double</type>
      <name>clasificar</name>
      <anchorfile>classPerceptron.html</anchorfile>
      <anchor>a411b4f88cc845628eca838871c44791a</anchor>
      <arglist>(vector&lt; double &gt; &amp;datos)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>sel_func</name>
      <anchorfile>classPerceptron.html</anchorfile>
      <anchor>a3ff2568151d83521cce53c1fc097e1c7</anchor>
      <arglist>(int x)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>fijar_tasa</name>
      <anchorfile>classPerceptron.html</anchorfile>
      <anchor>a035963219c55b200e834f265d73af9fb</anchor>
      <arglist>(double m)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>result</name>
      <anchorfile>classPerceptron.html</anchorfile>
      <anchor>a8941a21b88515424a7dbd84c96cf9c6a</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>particionar</name>
      <anchorfile>classPerceptron.html</anchorfile>
      <anchor>a3428383e94305e40bcc8442b9dd5ce2d</anchor>
      <arglist>(int cant, float porc)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>mostrar_pesos</name>
      <anchorfile>classPerceptron.html</anchorfile>
      <anchor>a405ec71b9f95adb1dd5f7c421ade36c7</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>graficar</name>
      <anchorfile>classPerceptron.html</anchorfile>
      <anchor>abbf13c8b567b0f3fcf9298573c038c49</anchor>
      <arglist>()</arglist>
    </member>
  </compound>
</tagfile>
