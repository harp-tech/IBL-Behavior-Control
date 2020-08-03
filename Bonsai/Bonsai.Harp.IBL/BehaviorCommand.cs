using Bonsai.Expressions;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Linq.Expressions;
using System.Reactive.Linq;
using System.ComponentModel;

namespace Bonsai.Harp.IBL.Behavior
{
    public enum IblBehaviorCommandType : byte
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

    public class IblBehaviorCommand : SelectBuilder, INamedElement
    {
        public IblBehaviorCommand()
        {
            Type = IblBehaviorCommandType.DataTo1KHz;
        }

        string INamedElement.Name
        {
            //get { return typeof(IblBehaviorCommand).Name.Replace("Command", string.Empty) + "." + Type.ToString(); }
            get { return Type.ToString(); }
        }

        public IblBehaviorCommandType Type { get; set; }

        protected override Expression BuildSelector(Expression expression)
        {
            switch (Type)
            {
                /************************************************************************/
                /* Register: CONFIG                                                     */
                /************************************************************************/
                case IblBehaviorCommandType.DataToQuiet:
                    return Expression.Call(typeof(IblBehaviorCommand), "ProcessDataToQuiet", new[] { expression.Type }, expression);

                case IblBehaviorCommandType.DataTo1KHz:
                    return Expression.Call(typeof(IblBehaviorCommand), "ProcessDataTo1KHz", new[] { expression.Type }, expression);

                /************************************************************************/
                /* Registers: DIGITAL_OUT                                               */
                /************************************************************************/
                case IblBehaviorCommandType.SetOutputs:
                    if (expression.Type != typeof(byte)) { expression = Expression.Convert(expression, typeof(byte)); }
                    return Expression.Call(typeof(IblBehaviorCommand), "ProcessSetOutputs", null, expression);

                case IblBehaviorCommandType.ClearOutputs:
                    if (expression.Type != typeof(byte)) { expression = Expression.Convert(expression, typeof(byte)); }
                    return Expression.Call(typeof(IblBehaviorCommand), "ProcessClearOutputs", null, expression);

                case IblBehaviorCommandType.ToggleOutputs:
                    if (expression.Type != typeof(byte)) { expression = Expression.Convert(expression, typeof(byte)); }
                    return Expression.Call(typeof(IblBehaviorCommand), "ProcessToggleOutputs", null, expression);

                case IblBehaviorCommandType.WriteOutputs:
                    if (expression.Type != typeof(byte)) { expression = Expression.Convert(expression, typeof(byte)); }
                    return Expression.Call(typeof(IblBehaviorCommand), "ProcessWriteOutputs", null, expression);

                /************************************************************************/
                /* Register: WRITE_A0                                                   */
                /************************************************************************/
                case IblBehaviorCommandType.WriteAnalogOutput:
                    if (expression.Type != typeof(float)) { expression = Expression.Convert(expression, typeof(float)); }
                    return Expression.Call(typeof(IblBehaviorCommand), "ProcessWriteAnalogOutput", null, expression);

                case IblBehaviorCommandType.WriteRegisterAnalogOutput:
                    if (expression.Type != typeof(UInt16)) { expression = Expression.Convert(expression, typeof(UInt16)); }
                    return Expression.Call(typeof(IblBehaviorCommand), "ProcessWriteRegisterAnalogOutput", null, expression);

                /************************************************************************/
                /* Register: ENCODER                                                    */
                /************************************************************************/
                case IblBehaviorCommandType.WriteEncoder:
                    if (expression.Type != typeof(Int16)) { expression = Expression.Convert(expression, typeof(Int16)); }
                    return Expression.Call(typeof(IblBehaviorCommand), "ProcessWriteEncoder", null, expression);

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
