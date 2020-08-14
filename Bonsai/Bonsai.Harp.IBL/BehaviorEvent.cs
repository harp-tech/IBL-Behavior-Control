using Bonsai;
using Bonsai.Expressions;
using OpenCV.Net;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Reactive.Linq;
using System.Text;
using TResult = System.String;
using System.ComponentModel;

namespace Bonsai.Harp.IBL
{
    public enum BehaviorEventType : byte
    {
        /* Event: DATA_STREAMM */
        AnalogSensor = 0,
        AnalogInput,
        Encoder,
        AnalogSensorTh0,
        AnalogSensorTh1,
        AnalogInputTh0,
        AnalogInputTh1,
        EncoderTh0,
        EncoderTh1,

        /* Event: INPUTS */
        InputIO0,
        InputIO1,
        InputIO2,
        UserInput,

        /* Raw data */
        RegisterAnalogSensor,
        RegisterAnalogInput,
        RegisterInputs

    }

    [Description(
        "\n" +
        "AnalogSensor: Integer" +
        "AnalogInput: Integer" +
        "Encoder: Integer" +
        "\n" +
        "AnalogSensorTh0: Boolean (*)" +
        "AnalogSensorTh1: Boolean (*)" +
        "AnalogInputTh0: Boolean (*)" +
        "AnalogInputTh1: Boolean (*)" +
        "EncoderTh0: Boolean (*)" +
        "EncoderTh1: Boolean (*)" +
        "\n" +
        "InputIO0: Boolean (*)\n" +
        "InputIO1: Boolean (*)\n" +
        "InputIO2: Boolean (*)\n" +
        "UserInput: Boolean (*)\n" +
        "\n" +
        "RegisterAnalogSensor: Bitmask\n" +
        "RegisterAnalogInput: Bitmask\n" +
        "RegisterInputs: Bitmask\n" +
        "\n" +
        "(*) Only distinct contiguous elements are propagated."
    )]

    public class BehaviorEvent : SingleArgumentExpressionBuilder, INamedElement
    {
        public BehaviorEvent()
        {
            Type = BehaviorEventType.AnalogSensor;
        }

        string INamedElement.Name
        {
            //get { return typeof(IblBehaviorEvent).Name.Replace("Event", string.Empty) + "." + Type.ToString(); }
            get { return Type.ToString(); }
        }

        public BehaviorEventType Type { get; set; }

        public override Expression Build(IEnumerable<Expression> expressions)
        {
            var expression = expressions.First();
            switch (Type)
            {
                /************************************************************************/
                /* Register: DATA_STREAM                                                */
                /************************************************************************/
                case BehaviorEventType.AnalogSensor:
                    return Expression.Call(typeof(BehaviorEvent), "ProcessAnalogSensor", null, expression);

                case BehaviorEventType.AnalogInput:
                    return Expression.Call(typeof(BehaviorEvent), "ProcessAnalogInput", null, expression);
                
                case BehaviorEventType.Encoder:
                    return Expression.Call(typeof(BehaviorEvent), "ProcessEncoder", null, expression);

                /************************************************************************/
                /* Register: DATA_STREAM (registers)                                    */
                /************************************************************************/

                case BehaviorEventType.RegisterAnalogSensor:
                    return Expression.Call(typeof(BehaviorEvent), "ProcessRegisterAnalogSensor", null, expression);

                case BehaviorEventType.RegisterAnalogInput:
                    return Expression.Call(typeof(BehaviorEvent), "ProcessRegisterAnalogInput", null, expression);

                /************************************************************************/
                /* Register: DATA_STREAM (thresholds)                                   */
                /************************************************************************/
                case BehaviorEventType.AnalogSensorTh0:
                    return Expression.Call(typeof(BehaviorEvent), "ProcessAnalogSensorTh0", null, expression);

                case BehaviorEventType.AnalogSensorTh1:
                    return Expression.Call(typeof(BehaviorEvent), "ProcessAnalogSensorTh1", null, expression);

                case BehaviorEventType.AnalogInputTh0:
                    return Expression.Call(typeof(BehaviorEvent), "ProcessAnalogInputTh0", null, expression);

                case BehaviorEventType.AnalogInputTh1:
                    return Expression.Call(typeof(BehaviorEvent), "ProcessAnalogInputTh1", null, expression);

                case BehaviorEventType.EncoderTh0:
                    return Expression.Call(typeof(BehaviorEvent), "ProcessEncoderTh0", null, expression);

                case BehaviorEventType.EncoderTh1:
                    return Expression.Call(typeof(BehaviorEvent), "ProcessEncoderTh1", null, expression);

                /************************************************************************/
                /* Register: INPUTS                                                     */
                /************************************************************************/
                case BehaviorEventType.InputIO0:
                    return Expression.Call(typeof(BehaviorEvent), "ProcessInputIO0", null, expression);

                case BehaviorEventType.InputIO1:
                    return Expression.Call(typeof(BehaviorEvent), "ProcessInputIO1", null, expression);

                case BehaviorEventType.InputIO2:
                    return Expression.Call(typeof(BehaviorEvent), "ProcessInputIO2", null, expression);

                case BehaviorEventType.UserInput:
                    return Expression.Call(typeof(BehaviorEvent), "ProcessUserInput", null, expression);


                /************************************************************************/
                /* Register: INPUTS (register)                                          */
                /************************************************************************/
                case BehaviorEventType.RegisterInputs:
                    return Expression.Call(typeof(BehaviorEvent), "ProcessRegisterInputs", null, expression);


                /************************************************************************/
                /* Default                                                              */
                /************************************************************************/
                default:
                    throw new InvalidOperationException("Invalid selection or not supported yet.");
            }
        }

        static double ParseTimestamp(byte[] message, int index)
        {
            var seconds = BitConverter.ToUInt32(message, index);
            var microseconds = BitConverter.ToUInt16(message, index + 4);
            return seconds + microseconds * 32e-6;
        }

        static bool is_evt33(HarpMessage input) { return ((input.Address == 33) && (input.Error == false) && (input.MessageType == MessageType.Event)); }
        static bool is_evt34(HarpMessage input) { return ((input.Address == 34) && (input.Error == false) && (input.MessageType == MessageType.Event)); }

        /************************************************************************/
        /* Register: DATA_STREAM                                                */
        /************************************************************************/
        static IObservable<float> ProcessAnalogSensor(IObservable<HarpMessage> source)
        {
            return source.Where(is_evt33).Select(input => { return BitConverter.ToInt16(input.MessageBytes, 11) * (float)3.3/(float)16384.0; });
        }

        static IObservable<float> ProcessAnalogInput(IObservable<HarpMessage> source)
        {
            return source.Where(is_evt33).Select(input => { return BitConverter.ToInt16(input.MessageBytes, 13) * (float)2.048 / (float)4096.0 / (float)0.4; });
        }

        static IObservable<Int16> ProcessEncoder(IObservable<HarpMessage> source)
        {
            return source.Where(is_evt33).Select(input => { return BitConverter.ToInt16(input.MessageBytes, 15); });
        }

        /************************************************************************/
        /* Register: DATA_STREAM (registers)                                    */
        /************************************************************************/

        static IObservable<Int16> ProcessRegisterAnalogSensor(IObservable<HarpMessage> source)
        {
            return source.Where(is_evt33).Select(input => { return BitConverter.ToInt16(input.MessageBytes, 11); });
        }
        static IObservable<Int16> ProcessRegisterAnalogInput(IObservable<HarpMessage> source)
        {
            return source.Where(is_evt33).Select(input => { return BitConverter.ToInt16(input.MessageBytes, 13); });
        }

        /************************************************************************/
        /* Register: DATA_STREAM (thresholds)                                   */
        /************************************************************************/
        static IObservable<bool> ProcessAnalogSensorTh0(IObservable<HarpMessage> source)
        {
            return source.Where(is_evt33).Select(input => { return ((input.MessageBytes[17] & (1 << 0)) == (1 << 0)); }).DistinctUntilChanged();
        }
        static IObservable<bool> ProcessAnalogSensorTh1(IObservable<HarpMessage> source)
        {
            return source.Where(is_evt33).Select(input => { return ((input.MessageBytes[17] & (1 << 1)) == (1 << 1)); }).DistinctUntilChanged();
        }
        static IObservable<bool> ProcessAnalogInputTh0(IObservable<HarpMessage> source)
        {
            return source.Where(is_evt33).Select(input => { return ((input.MessageBytes[17] & (1 << 2)) == (1 << 2)); }).DistinctUntilChanged();
        }
        static IObservable<bool> ProcessAnalogInputTh1(IObservable<HarpMessage> source)
        {
            return source.Where(is_evt33).Select(input => { return ((input.MessageBytes[17] & (1 << 3)) == (1 << 3)); }).DistinctUntilChanged();
        }
        static IObservable<bool> ProcessEncoderTh0(IObservable<HarpMessage> source)
        {
            return source.Where(is_evt33).Select(input => { return ((input.MessageBytes[17] & (1 << 4)) == (1 << 4)); }).DistinctUntilChanged();
        }
        static IObservable<bool> ProcessEncoderTh1(IObservable<HarpMessage> source)
        {
            return source.Where(is_evt33).Select(input => { return ((input.MessageBytes[17] & (1 << 5)) == (1 << 5)); }).DistinctUntilChanged();
        }

        /************************************************************************/
        /* Register: INPUTS                                                     */
        /************************************************************************/
        static IObservable<bool> ProcessInputIO0(IObservable<HarpMessage> source)
        {
            return source.Where(is_evt34).Select(input => { return ((input.MessageBytes[11] & (1 << 0)) == (1 << 0)); }).DistinctUntilChanged();
        }

        static IObservable<bool> ProcessInputIO1(IObservable<HarpMessage> source)
        {
            return source.Where(is_evt34).Select(input => { return ((input.MessageBytes[11] & (1 << 1)) == (1 << 1)); }).DistinctUntilChanged();
        }

        static IObservable<bool> ProcessInputIO2(IObservable<HarpMessage> source)
        {
            return source.Where(is_evt34).Select(input => { return ((input.MessageBytes[11] & (1 << 2)) == (1 << 2)); }).DistinctUntilChanged();
        }

        static IObservable<bool> ProcessUserInput(IObservable<HarpMessage> source)
        {
            return source.Where(is_evt34).Select(input => { return ((input.MessageBytes[11] & (1 << 3)) == (1 << 3)); }).DistinctUntilChanged();
        }

        /************************************************************************/
        /* Register: DIGITAL_IN                                                 */
        /************************************************************************/
        static IObservable<bool> ProcessDigitalIn(IObservable<HarpMessage> source)
        {
            return source.Where(is_evt34).Select(input => { return ((input.MessageBytes[11] & (1 << 0)) == (1 << 0)); });
        }

        /************************************************************************/
        /* Register: INPUTS (register)                                          */
        /************************************************************************/
        static IObservable<byte> ProcessRegisterInputs(IObservable<HarpMessage> source)
        {
            return source.Where(is_evt34).Select(input => { return (input.MessageBytes[11]); });
        }
    }
}
