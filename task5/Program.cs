using System;
using System.Collections.Generic;
using System.Linq;


namespace Task5
{
    class HashTable
    {
        private int B;
        private List<double>[] table;
        public static int a = 1;
        public static int c = 2;

        public HashTable(int B)
        { 
            this.B = B;
            table = new List<double>[B];
            for (int i = 0; i < B; i++)
                table[i] = new List<double>();
        }

        private int GetHash(double x)
        {
            if (B < 20000)
                return (int)x % B;
            else
                return (int)(a * x + c) % B;
        }

        public void Insert(double value)
        {
            table[GetHash(value)].Add(value);
        }

        public bool Search(double value) => table[GetHash(value)].Contains(value);

        public int GetCollisions() => table.Count(val => val.Count > 1);

        public void Print()
        {
            Console.WriteLine("Хеш-таблица:");
            for (int i = 0; i < B; i++)
                if (table[i].Count > 0)
                    Console.WriteLine($"{i}: [{string.Join("; ", table[i])}]");
        }
    }
    
    internal class Program
    {
        static void Main(string[] args)
        {
            int b;
            HashTable ht;
            Random random = new Random();

            Console.Write("Введите число B: ");
            b = Convert.ToInt32(Console.ReadLine());

            ht = new HashTable(b);
            for (int i = 0; i < b * 2; i++)
                ht.Insert(random.Next(10, 1000) / 10.0);
            ht.Print();

            Console.Write("Введите число B: ");
            b = Convert.ToInt32(Console.ReadLine());

            HashTable.a = 2;
            HashTable.c = 10;

            ht = new HashTable(b);
            for (int i = 0; i < b; i++)
                ht.Insert(random.Next(10, 10000) / 10.0);
            Console.Write("Введите элемент для поиска: ");
            double query = Convert.ToDouble(Console.ReadLine());
            Console.WriteLine($"Элемент {(ht.Search(query) ? "" : "не ")}найден");
            int collisionsCount = ht.GetCollisions();
            Console.WriteLine($"Количество коллизий: {collisionsCount}");
        }
    }
}
