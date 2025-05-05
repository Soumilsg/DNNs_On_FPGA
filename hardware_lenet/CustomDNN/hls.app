<project xmlns="com.autoesl.autopilot.project" name="CustomDNN" top="cnn_top">
    <includePaths/>
    <libraryPaths/>
    <Simulation>
        <SimFlow name="csim"/>
    </Simulation>
    <files xmlns="">
        <file name="../../testbench.cpp" sc="0" tb="1" cflags=" -Wno-unknown-pragmas -Wno-unknown-pragmas" csimflags=" -Wno-unknown-pragmas" blackbox="false"/>
        <file name="cnn_top.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="cnn_top.h" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="conv2d_layer1.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="conv2d_layer1.h" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="conv2d_layer2.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="conv2d_layer2.h" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="dense_layer1.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="dense_layer1.h" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="dense_layer2.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="dense_layer2.h" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="flatten.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="flatten.h" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="maxPool_layer1.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="maxPool_layer1.h" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="maxPool_layer2.cpp" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
        <file name="maxPool_layer2.h" sc="0" tb="false" cflags="" csimflags="" blackbox="false"/>
    </files>
    <solutions xmlns="">
        <solution name="solution1" status="active"/>
    </solutions>
</project>

