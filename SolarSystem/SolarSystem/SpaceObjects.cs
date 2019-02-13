using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Media;

namespace SolarSystem
{
    public class SpaceObjects
    {
        public String name { get; set; }
        public double orbitalRadius;
        protected int orbitalPeriode;
        public int objRadius;
        protected double rotationPeriode;
        public String color;

        public SpaceObjects(String name, double orbitalRadius, int orbitalPeriode, int objRadius, double rotationPeriode, String color)
        {
            this.name = name;
            this.orbitalRadius = orbitalRadius;
            this.orbitalPeriode = orbitalPeriode;
            this.objRadius = objRadius;
            this.rotationPeriode = rotationPeriode;
            this.color = color;

        }

        public virtual void Draw()
        {
            Console.WriteLine(name);
            Console.WriteLine("Orbital radius: " + orbitalRadius);
            Console.WriteLine("Orbital periode: " + orbitalPeriode + " days");
            Console.WriteLine("Object radius: " + objRadius + " km");
            Console.WriteLine("Lengt of day: " + rotationPeriode + " days");
            Console.WriteLine("Color: " + color);
   
        }
 
        public Tuple<double, double> CalcPosition(double time)
        {
            double x;
            double y;

            if (orbitalRadius != 0)
            {
                double radian = 2 * Math.PI * (time / orbitalPeriode);

                x = orbitalRadius * Math.Cos(radian);
                y = orbitalRadius * Math.Sin(radian);
            } else
            {
                x = 0;
                y = 0;
            }

            return Tuple.Create(x, y);

        }
 
    }

    public class Planet : SpaceObjects
    {
        public Planet(String Name, double orbitalRadius, int orbitalPeriode, int objRadius, double rotationPeriode, String color) :
            base(Name, orbitalRadius, orbitalPeriode, objRadius, rotationPeriode, color){  }
        public override void Draw()
        {
            Console.Write("Planet:      ");
            base.Draw();
            Console.Write("\n");

        }

    }

    public class Star : SpaceObjects
    {
        public Star (String name, double orbitalRadius, int orbitalPeriode, int objRadius, double rotationPeriode, String color) :
            base(name, orbitalRadius, orbitalPeriode, objRadius, rotationPeriode, color){ }
        public override void Draw()
        {
            Console.Write("Star:        ");
            base.Draw();
            Console.Write("\n");

        }
    }

    public class Moon : SpaceObjects
    {
        public SpaceObjects parent { get; set; }
        public Moon(String name, double orbitalRadius, int orbitalPeriode, int objRadius, double rotationPeriode, String color, SpaceObjects parent) :
            base(name, orbitalRadius, orbitalPeriode, objRadius, rotationPeriode, color) { this.parent = parent;}
        public override void Draw()
        {
            
            Console.Write("Moon:        ");
            base.Draw();
            if (parent != null)
                Console.WriteLine("Orbits around: " + parent.name + "\n");
            
        }
        public override String ToString()
        {
            return ("Name: " + name + ", OrbitalRadius: " + orbitalRadius + ", Radius: " + objRadius + ", Color: " + color);
        }

    }

    public class Asteroid : SpaceObjects
    {
        public Asteroid(String name, double orbitalRadius, int orbitalPeriode, int objRadius, double rotationPeriode, String color) :
            base(name, orbitalRadius, orbitalPeriode, objRadius, rotationPeriode, color)
        { }
        public override void Draw()
        {
            Console.Write("Asteroid:     ");
            base.Draw();
            Console.Write("\n");
        }
    }

    public class DwarfPlanet : SpaceObjects
    {
        public DwarfPlanet(String name, double orbitalRadius, int orbitalPeriode, int objRadius, double rotationPeriode, String color) :
            base(name, orbitalRadius, orbitalPeriode, objRadius, rotationPeriode, color)
        { }
        public override void Draw()
        {
            Console.Write("Dwarf Planet:    ");
            base.Draw();
            Console.Write("\n");

        }
    }


}
