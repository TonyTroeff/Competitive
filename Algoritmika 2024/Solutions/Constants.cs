namespace Solutions;

public static class Constants
{
    public static class Problem2
    {
        public static readonly string[] Severities = ["Normal", "Unknown", "Warning", "Critical"];
        public static readonly string[] Devices = [string.Empty, "Power block", "Outgoing communication", "Incoming communication", "Camera", "Engine", string.Empty, string.Empty]; 
        public static readonly string[] Damages = [string.Empty, "Overheating", "No reaction", "Lost communication", "High energy consumption", "Damage in electronics", string.Empty, string.Empty]; 
    }
}