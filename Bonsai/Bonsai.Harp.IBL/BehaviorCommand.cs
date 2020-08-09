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
    public enum BehaviorCommandType : byte
    {
        DataToQuiet,
        DataTo1KHz,

        SetOutputs,
        ClearOutputs,
        ToggleOutputs,
        WriteOutputs,

        WriteAnalogOutput,
        WriteEncoder,

        WriteRegisterAnalogOutput
    }

    [Description(
        "\n" +
        "DataToQuiet: Any\n" +
        "DataTo1KHz: Any\n" +
        "\n" +
        "SetOutputs: Bitmask\n" +
        "ClearOutput: Bitmask\n" +
        "ToggleOutputs: Bitmask\n" +
        "WriteOutputs: Bitmask\n" +
        "\n" +
        "WriteAnalogOutput: Float\n" +
        "WriteEncoder: Float\n" +
        "\n" +
        "WriteRegisterAnalogOutput: U16"
    )]

    public class BehaviorCommand : SelectBuilder, INamedElement
    {
        public BehaviorCommand()
        {
            Type = BehaviorCommandType.DataTo1KHz;
        }

        string INamedElement.Name
        {
            //get { return typeof(IblBehaviorCommand).Name.Replace("Command", string.Empty) + "." + Type.ToString(); }
            get { return Type.ToString(); }
        }

        public BehaviorCommandType Type { get; set; }

        protected override Expression BuildSelector(Expression expression)
        {
            switch (Type)
            {
                /************************************************************************/
                /* Register: CONFIG                                                     */
                /************************************************************************/
                case BehaviorCommandType.DataToQuiet:
                    return Expression.Call(typeof(BehaviorCommand), "ProcessDataToQuiet", new[] { expression.Type }, expression);

                case BehaviorCommandType.DataTo1KHz:
                    return Expression.Call(typeof(BehaviorCommand), "ProcessDataTo1KHz", new[] { expression.Type }, expression);

                /************************************************************************/
                /* Registers: DIGITAL_OUT                                               */
                /************************************************************************/
                case BehaviorCommandType.SetOutputs:
                    if (expression.Type != typeof(byte)) { expression = Expression.Convert(expression, typeof(byte)); }
                    return Expression.Call(typeof(BehaviorCommand), "ProcessSetOutputs", null, expression);

                case BehaviorCommandType.ClearOutputs:
                    if (expression.Type != typeof(byte)) { expression = Expression.Convert(expression, typeof(byte)); }
                    return Expression.Call(typeof(BehaviorCommand), "ProcessClearOutputs", null, expression);

                case BehaviorCommandType.ToggleOutputs:
                    if (expression.Type != typeof(byte)) { expression = Expression.Convert(expression, typeof(byte)); }
                    return Expression.Call(typeof(BehaviorCommand), "ProcessToggleOutputs", null, expression);

                case BehaviorCommandType.WriteOutputs:
                    if (expression.Type != typeof(byte)) { expression = Expression.Convert(expression, typeof(byte)); }
                    return Expression.Call(typeof(BehaviorCommand), "ProcessWriteOutputs", null, expression);

                /************************************************************************/
                /* Register: WRITE_A0                                                   */
                /************************************************************************/
                case BehaviorCommandType.WriteAnalogOutput:
                    if (expression.Type != typeof(float)) { expression = Expression.Convert(expression, typeof(float)); }
                    return Expression.Call(typeof(BehaviorCommand), "ProcessWriteAnalogOutput", null, expression);

                case BehaviorCommandType.WriteRegisterAnalogOutput:
                    if (expression.Type != typeof(UInt16)) { expression = Expression.Convert(expression, typeof(UInt16)); }
                    return Expression.Call(typeof(BehaviorCommand), "ProcessWriteRegisterAnalogOutput", null, expression);

                /************************************************************************/
                /* Register: ENCODER                                                    */
                /************************************************************************/
                case BehaviorCommandType.WriteEncoder:
                    if (expression.Type != typeof(Int16)) { expression = Expression.Convert(expression, typeof(Int16)); }
                    return Expression.Call(typeof(BehaviorCommand), "ProcessWriteEncoder", null, expression);

                default:
                    break;
            }
            return expression;
        }

        /************************************************************************/
        /* Register: CONFIG                                                     */
        /************************************************************************/
        static HarpMessage ProcessDataToQuiet<TSource>(TSource input)
        {
            return new HarpMessage(true, 2, 6, 32, 255, (byte)PayloadType.U16, 0, 32, 0);
        }
        static HarpMessage ProcessDataTo1KHz<TSource>(TSource input)
        {
            return new HarpMessage(true, 2, 6, 32, 255, (byte)PayloadType.U16, 0, 64, 0);
        }

        /************************************************************************/
        /* Register: OUTPUT_x                                                   */
        /************************************************************************/
        static HarpMessage ProcessSetOutputs(byte input)
        {
            return new HarpMessage(true, 2, 5, 38, 255, (byte)PayloadType.U8, input, 0);
        }
        static HarpMessage ProcessClearOutputs(byte input)
        {
            return new HarpMessage(true, 2, 5, 39, 255, (byte)PayloadType.U8, input, 0);
        }
        static HarpMessage ProcessToggleOutputs(byte input)
        {
            return new HarpMessage(true, 2, 5, 40, 255, (byte)PayloadType.U8, input, 0);
        }
        static HarpMessage ProcessWriteOutputs(byte input)
        {
            return new HarpMessage(true, 2, 5, 41, 255, (byte)PayloadType.U8, input, 0);
        }

        /************************************************************************/
        /* Register: WRITE_A0                                                   */
        /************************************************************************/
        static HarpMessage ProcessWriteAnalogOutput(float input)
        {
            input = input / (float)(3.3 / 4096.0);
            if (input < 0) input = 0;
            if (input > 4096 - 1) input = 4096 - 1;

            UInt16 register = (UInt16)input;

            return new HarpMessage(true, 2, 6, 73, 255, (byte)PayloadType.U16, (byte)(register & 255), (byte)((register >> 8) & 255), 0);
        }

        static HarpMessage ProcessWriteRegisterAnalogOutput(UInt16 input)
        {
            return new HarpMessage(true, 2, 6, 73, 255, (byte)PayloadType.U16, (byte)(input & 255), (byte)((input >> 8) & 255), 0);
        }
        /************************************************************************/
        /* Register: WRITE_ENCODER                                              */
        /************************************************************************/
        static HarpMessage ProcessWriteEncoder(Int16 input)
        {
            return new HarpMessage(true, 2, 6, 74, 255, (byte)PayloadType.U16, (byte)(input & 255), (byte)((input >> 8) & 255), 0);
        }
    }
}
