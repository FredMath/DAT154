using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SolarSystem
{
    public class Planet : SpaceObjects
    {
        public Planet(String Name, double orbitalRadius, int orbitalPeriode, int objRadius, double rotationPeriode, String color) :
            base(Name, orbitalRadius, orbitalPeriode, objRadius, rotationPeriode, color)
        { }
        public override void Draw()
        {
            Console.Write("Planet:      ");
            base.Draw();
            Console.Write("\n");

        }

    }
}
