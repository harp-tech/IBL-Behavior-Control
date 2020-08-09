using Bonsai.Expressions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Linq.Expressions;
using System.Reactive.Linq;
using System.ComponentModel;

namespace Bonsai.Harp.IBL
{
    [Flags]
    public enum Ports : byte
    {
        IO0 = (1 << 0),
        IO1 = (1 << 1),
        IO2 = (1 << 2)
    }

    public enum BehaviorCommandDigOutputsType : byte
    {
        Set,
        Clear,
        Toggle
    }

    [Description(
        "Set: Any\n" +
        "Clear: Any\n" +
        "Toggle: Any\n"
    )]



    public class BehaviorCommandDigOutputs : SelectBuilder, INamedElement
    {
        public BehaviorCommandDigOutputs()
        {
            Type = BehaviorCommandDigOutputsType.Set;
            Mask = Ports.IO0;
        }

        string INamedElement.Name
        {
            //get { return typeof(IblBehaviorCommand).Name.Replace("Command", string.Empty) + "." + Type.ToString(); }
            get
            {
                var NodeName = Type.ToString() + "." + Mask.ToString();
                int NumberOfChoices = NodeName.Count(f => f == ',') + 1;
                Console.WriteLine(NumberOfChoices);
                NodeName = NodeName.Replace(" ", "");   // Remove the spaces

                if (NumberOfChoices > 1)
                    return NodeName.Replace(".", ".\n");
                else
                    return NodeName;
            }
        }

        public BehaviorCommandDigOutputsType Type { get; set; }
        public Ports Mask { get; set; }

        protected override Expression BuildSelector(Expression expression)
        {
            switch (Type)
            {
                /************************************************************************/
                /* Registers: DIGITAL_OUT                                               */
                /************************************************************************/
                case BehaviorCommandDigOutputsType.Set:
                    return Expression.Call(typeof(BehaviorCommandDigOutputs), "ProcessSetOutputs", new[] { expression.Type }, expression, GetBitMask());

                case BehaviorCommandDigOutputsType.Clear:
                    return Expression.Call(typeof(BehaviorCommandDigOutputs), "ProcessClearOutputs", new[] { expression.Type }, expression, GetBitMask());

                case BehaviorCommandDigOutputsType.Toggle:
                    return Expression.Call(typeof(BehaviorCommandDigOutputs), "ProcessToggleOutputs", new[] { expression.Type }, expression, GetBitMask());

                default:
                    break;
            }
            return expression;
        }

        /************************************************************************/
        /* Local functions                                                      */
        /************************************************************************/
        Expression GetBitMask()
        {
            return Expression.Convert(Expression.Constant(Mask), typeof(byte));
        }

        static byte GetMask(byte BonsaiBitMaks)
        {
            return BonsaiBitMaks;
        }

        /************************************************************************/
        /* Register: OUTPUT_x                                                   */
        /************************************************************************/
        static HarpMessage ProcessSetOutputs<TSource>(TSource input, byte bMask)
        {
            return new HarpMessage(true, 2, 5, 38, 255, (byte)PayloadType.U8, GetMask(bMask), 0);
        }
        static HarpMessage ProcessClearOutputs<TSource>(TSource input, byte bMask)
        {
            return new HarpMessage(true, 2, 5, 39, 255, (byte)PayloadType.U8, GetMask(bMask), 0);
        }
        static HarpMessage ProcessToggleOutputs<TSource>(TSource input, byte bMask)
        {
            return new HarpMessage(true, 2, 5, 40, 255, (byte)PayloadType.U8, GetMask(bMask), 0);
        }
    }
}
