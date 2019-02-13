using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SolarSystem
{
    public class Star : SpaceObjects
    {
        public Star(String name, double orbitalRadius, int orbitalPeriode, int objRadius, double rotationPeriode, String color) :
            base(name, orbitalRadius, orbitalPeriode, objRadius, rotationPeriode, color)
        { }
        public override void Draw()
        {
            Console.Write("Star:        ");
            base.Draw();
            Console.Write("\n");

        }
    }
}
