---


---

<h1 id="可自动识谱的机械臂与灵巧手的弹琴系统">可自动识谱的机械臂与灵巧手的弹琴系统</h1>
<h2 id="系统介绍">系统介绍</h2>
<p>该系统通过摄像头拍下需要弹奏乐曲的五线谱的图片，通过audiveris 开源软件识别图片中的乐谱信息（包括音值、音长、节奏、速度以及乐理符号等）并生成标准可视化的MusicXML文件，然后通过全局规划算法计算出乐曲中每个音符的弹奏指法、机械臂移动位置坐标等具体信息，最后基于ROS控制机械臂与灵巧手的运动，根据计算得到的数据信息，完成拟人化的电子琴演奏。</p>
<h2 id="安装说明">安装说明</h2>
<p>该系统所依赖的功能包或库文件包含以下内容：</p>
<ol>
<li>audiveris （系统视觉自动识谱部分）<br>
源码链接：<a href="https://github.com/Audiveris/audiveris">https://github.com/Audiveris/audiveris</a><br>
具体说明在audiveris文件的readme中<br>
安装运行说明书链接：<a href="https://bacchushlg.gitbooks.io/audiveris-5-1/content/install/sources.html">https://bacchushlg.gitbooks.io/audiveris-5-1/content/install/sources.html</a></li>
<li>aubo_robot （系统机械臂与灵巧手的控制部分）<br>
源码链接：<a href="https://github.com/zhaoyuRobotics/aubo_robot">https://github.com/zhaoyuRobotics/aubo_robot</a><br>
本项目控制部分的主程序基于此开源项目编写，参考的关键代码文件为aubo_robot/aubo_demo/src/MoveGroupInterface_To_Kinetic.cpp</li>
</ol>
<h2 id="主要器件">主要器件</h2>
<ol>
<li>DH5-031L拟人灵巧手</li>
<li>61键电子琴</li>
<li>AUBO-i5机械臂</li>
<li>网线、USB转串口线</li>
<li>摄像头</li>
<li>电脑</li>
</ol>
<h2 id="环境搭建">环境搭建</h2>
<p>操作系统为Ubuntu16.04，并且需要搭建ROS开发环境。电脑主机通过网线连接AUBO-i5机械臂的机箱进行通信，通过USB转串口线与灵巧手连接进行控制。摄像头通过USB口与电脑连接，无需安装驱动可直接识别。</p>
<h2 id="使用说明">使用说明</h2>
<pre><code>python camera.py
</code></pre>
<p>功能：打开摄像头，按q键截图，保存路径可在camera文件中修改，默认路径为/home/franklin/Desktop/xml2vec-master/music.png</p>
<p>进入audiveris 文件夹，然后运行以下命令：</p>
<pre><code>./gradlew build (只需运行一次)
./gradlew run
</code></pre>
<p>此时若运行成功将弹出乐谱识别软件窗口，然后点击菜单栏中的File按钮，再点击Input按钮，然后选择刚才通过摄像头的截图导入。导入成功后主界面将显示此截图。然后点击菜单栏中的Book按钮，再点击Export Book As按钮，导出路径以及导出文件名称可自行设定，注意需要与solve_xml.py文件中的filename后的路径相同，默认为<code>/home/franklin/Desktop/music.mxl</code></p>
<p>成功导出后执行命令：</p>
<pre><code>python solve_xml.py
</code></pre>
<p>该命令功能为解析audiveris软件生成的.mxl文件并生成压缩包，然后自动解压出标准的MusicXML文件，并放置在与solve_xml.py文件同级目录下。默认文件名称为： music.xml</p>
<p>继续执行命令：</p>
<pre><code>python show_xml.py music.xml yuepu.xml
</code></pre>
<p>该命令生成test.txt 和 yuepu.xml两个文件，均为解析的中间数据。test.txt文件后面需要用到，切勿删除。yuepu.xml文件为进一步分析数据，仅供参考。<br>
然后编译并运行main.cpp文件后，生成planning_result.txt文件。该文件记录了乐谱中每个音符的音值、分配的灵巧手指以及时值。</p>
<p>机械臂与灵巧手控制部分</p>
<pre><code>cd /home/franklin/catkin_ws
catkin_make
</code></pre>
<p>进入到catkin_ws目录下然后编译软件包，编译完成后执行以下命令：</p>
<pre><code>roslaunch aubo_i5_moveit_config moveit_planning_execution.launch robot_ip:=192.168.199.200

roslaunch aubo_demo move_group_interface_tutorial.launch 
</code></pre>
<p>第一条命令中robot_ip后的ip地址为机械臂的地址，需要根据实际情况进行设定，原则上应当与电脑设定的ip地址位于同一网关，运行前需要进行ping测试，以保证电脑主机能够通过网线与机械臂建立好连接。</p>
<p>按照上述流程依次执行，系统可正常进行自动识谱与弹琴演奏。</p>

