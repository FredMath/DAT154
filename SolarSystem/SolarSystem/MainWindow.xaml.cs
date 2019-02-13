using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;
using System.Windows.Threading;


namespace SolarSystem
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private double maxSizePlanet = 60268;
        public List<SpaceObjects> solarSystem;
        public List<Moon> planetMoons = new List<Moon>();
        private double origoX;
        private double origoY;
        private double time = 0;
        private List<double> times = new List<double>();
        private List<Point> positions = new List<Point>();
        private double MoveSpeed = 0.3;
        private Tuple<double, double> pos;

        private const bool RANDOMSTART = true;
        private Random random = new Random(DateTime.Now.Second);
        public MainWindow()
        {

            InitializeComponent();

            solarSystem = InitSolarSystem();
            Moons();
            Loaded += delegate
            {
                origoX = spaceScreen.ActualWidth / 2;
                origoY = spaceScreen.ActualHeight / 2;
                Canvas myCanvas = new Canvas {};
                for (int i = 0; i < solarSystem.Count; i++)
                {
                    pos = solarSystem[i].CalcPosition(time);
                    Ellipse el = DrawSpaceObject(i, pos);
                    spaceFrame.Children.Add(el);

                    Ellipse orb = DrawOrbit(i, pos);
                    orbitFrame.Children.Add(orb);
                }

            };

                DispatcherTimer Timer = new DispatcherTimer
            {
                Interval = new TimeSpan(15000)
            };
            Timer.Tick += DispatcherTimer_tick;
            Timer.Start();

        }

        private void DispatcherTimer_tick(object sender, EventArgs e)
        {
            time += MoveSpeed;
            UpdatePosition();
        }

        public Ellipse DrawSpaceObject(int i, Tuple<double, double> pos)
        {
            double posX = 0;
            double posY = 0;


            Ellipse el = new Ellipse
            {
                Name = solarSystem[i].name,
                Fill = new SolidColorBrush((Color)ColorConverter.ConvertFromString(solarSystem[i].color))
          
            };
            el.MouseLeftButtonDown += Ellipse_MouseLeftButtonDown;

            if (el.Name.Contains("Sun"))
               el.Width = 2 * Scale(solarSystem[i].objRadius, maxSizePlanet, 35.0);
            else
               el.Width = Scale(solarSystem[i].objRadius, maxSizePlanet, 35.0);
            el.Height = el.Width;
       
            posX = origoX + pos.Item1 - el.Width * 0.5;
            posY = origoY + pos.Item2 - el.Height * 0.5;
           
            positions.Add(new Point(posX, posY));
            Canvas.SetTop(el, posY);
            Canvas.SetLeft(el, posX);

            return el;

        }

        private void Ellipse_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            Ellipse el = (Ellipse)sender;
            SpaceObjects planet = null;
            foreach (SpaceObjects p in solarSystem)
            {
                if (el.Name == p.name)
                    planet = p;
            }

            MessageBox.Show(FindMoons(planet));

        }

        public Ellipse DrawOrbit(int i, Tuple<double, double> pos)
        {
            double posX = 0;
            double posY = 0;
            Ellipse orbit = new Ellipse
            {
                Height = 2 * solarSystem[i].orbitalRadius,
                Width = 2 * solarSystem[i].orbitalRadius
            };
            posX = (origoX + pos.Item1 - solarSystem[i].orbitalRadius * 0.5);
            posY = (origoY + pos.Item2 - solarSystem[i].orbitalRadius * 0.5);
            Canvas.SetLeft(orbit, posX - solarSystem[i].orbitalRadius * 1.5);
            Canvas.SetTop(orbit, posY - solarSystem[i].orbitalRadius * 0.5);
            orbit.Stroke = Brushes.White;
            orbit.StrokeThickness = 0.25;
            return orbit;
        }

        private void UpdatePosition()
        {
            double posX = 0;
            double posY = 0;
            

            for (int i = 0; i < solarSystem.Count; i++)
            {
                Ellipse e = (Ellipse)VisualTreeHelper.GetChild(spaceFrame, i);

                pos = solarSystem[i].CalcPosition(time);
                double posXCenter = origoX - e.Width * 0.5;
                double posYCenter = origoY - e.Height * 0.5;
                
                if (solarSystem[i] is Moon)
                {
                    Moon moon = (Moon)solarSystem[i];
                    SpaceObjects Parent = moon.parent;
                    Tuple<double, double> parentPos = Parent.CalcPosition(time);
                    posX = (posXCenter + parentPos.Item1) + pos.Item1;
                    posY = (posYCenter + parentPos.Item2) + pos.Item2;

                } else
                {
                    posX = origoX - e.Width * 0.5 + pos.Item1;
                    posY = origoY - e.Height * 0.5 + pos.Item2;
                }
                positions[i] = new Point(posX, posY);

                Canvas.SetTop(e, posY);
                Canvas.SetLeft(e, posX);

            }
        
        }

        public List<SpaceObjects> InitSolarSystem()
        {
            List<SpaceObjects> solarSystem = new List<SpaceObjects>();
            String file = "ObjectInfo.txt";
            String path = @"C:\Users\Fredrik Mathisen\source\repos\SolarSystem";

            String fullPath = System.IO.Path.Combine(path, file);
            String[] lines = System.IO.File.ReadAllLines(fullPath);

            String[][] jaggedArray = lines.Select(line => line.Split('\t').ToArray()).ToArray();

            foreach (string[] line in jaggedArray)
            {
                string obj = line[0];
                string Name = line[1];
                Double orbRadius = Double.Parse(line[2]);
                int orbitalPeriode = int.Parse(line[3]);
                int planetRadius = int.Parse(line[4]);
                double rotPeriode = Double.Parse(line[5]);
                String color = line[6];

                switch (obj)
                {
                    case "Star":
                        solarSystem.Add(new Star(Name, orbRadius, orbitalPeriode, planetRadius, rotPeriode, color));
                        break;
                    case "Moon":
                        SpaceObjects parent = FindParent(line[7], solarSystem);
                        solarSystem.Add(new Moon(Name, orbRadius, orbitalPeriode, planetRadius, rotPeriode, color, parent));

                        break;
                    case "DwarfPlanet":
                        solarSystem.Add(new DwarfPlanet(Name, orbRadius, orbitalPeriode, planetRadius, rotPeriode, color));
                        break;
                    default:
                        solarSystem.Add(new Planet(Name, orbRadius, orbitalPeriode, planetRadius, rotPeriode, color));
                        break;
                }
            }
            return solarSystem;

        }

        SpaceObjects FindParent(String name, List<SpaceObjects> solarSystem)
        {
            SpaceObjects Parent = null;
            foreach (SpaceObjects so in solarSystem)
            {
                if (name == so.name)
                {
                    Parent = so;
                    break;
                }
            }
            return Parent;
        }

        public Func<double, double, double, double> Scale = (value, maxInputValue, maxOutputValue) =>
        (value <= 1.0) ? 0.0 : Math.Log(value) * maxOutputValue / Math.Log(maxInputValue);

        public void Moons()
        {

            string file = "MoonObjects.txt";
            string path = @"C:\Users\Fredrik Mathisen\source\repos\SolarSystem";
            string fullPath = System.IO.Path.Combine(path, file);
            string[] lines = System.IO.File.ReadAllLines(fullPath);

            foreach(string s in lines)
            {
                string[] attribs = s.Split('\t');

                string name = attribs[0];
                double orbRadius = double.Parse(attribs[1]);
                int orbitalPeriode = int.Parse(attribs[2]);
                int moonRadius = int.Parse(attribs[3]);
                double rotPeriode = double.Parse(attribs[4]);
                string color = attribs[5];
                SpaceObjects parent = FindParent(attribs[6], solarSystem);


                planetMoons.Add(new Moon(name, orbRadius, orbitalPeriode, moonRadius, rotPeriode, color, parent));
               
                
            }

        }
        public String FindMoons(SpaceObjects p)
        {
            string s = "Moons: ";
            foreach (Moon m in planetMoons)
            {
                if (m.parent.name == p.name)
                {
                    s += '\n' + m.ToString();
                }
            }

            return s;
        }
    }   
}
