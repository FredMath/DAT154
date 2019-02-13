using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SolarSystem
{
    public class Moon : SpaceObjects
    {
        SpaceObjects parent;
        public Moon(String name, double orbitalRadius, int orbitalPeriode, int objRadius, double rotationPeriode, String color, SpaceObjects parent) :
            base(name, orbitalRadius, orbitalPeriode, objRadius, rotationPeriode, color)
        { this.parent = parent; }
        public override void Draw()
        {

            Console.Write("Moon:        ");
            base.Draw();
            if (parent != null)
                Console.WriteLine("Orbits around: " + parent.Name + "\n");
            else
                Console.WriteLine("Has no parent" + "\n");
        }

    }
}
